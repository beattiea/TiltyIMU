/*
TiltyIMU.cpp - A easy to use interface for the TiltyIMU line of circuit boards
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 2 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TiltyIMU.h"

TiltyIMU::TiltyIMU()
{
	// Instantiate sensors
	imu = MPU6050();
	magn = HMC5883();
	alt = MPL3115A2();
}


TiltyIMU::~TiltyIMU()
{
	// Do nothing
}


void TiltyIMU::init()
{
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE);//  Starts I2C on Teensy
	delay(5);

	hasIMU = imu.init();
	hasMagn = magn.init();
	hasAlt = alt.init();
	
	#ifdef DEBUG_INITS
		myPort.print("Has IMU: ");
		myPort.println(hasIMU);
		myPort.print("Has Compass: ");
		myPort.println(hasMagn);
		myPort.print("Has Altimeter: ");
		myPort.println(hasAlt);
		myPort.println();
	#endif
	
	if (hasIMU) initializeIMU();
}


// Initializes the IMU sensor
void TiltyIMU::initializeIMU()
{
#ifdef USE_DMP
	if (!imu.dmpInitialize())
	{
		imu.setDMPEnabled(true);
		packetSize = imu.dmpGetFIFOPacketSize();
		
		#ifdef DEBUG_INITS
			myPort.println("DMP initialized...\n");
		#endif
	}
	#ifdef DEBUG_INITS
	else
	{
			myPort.println("DMP not initialized! Something has gone worng!\n");
	}
	#endif
#endif
}


// Reads the various available sensors to determine if there is new data available.
// If new data is available it is downloaded from the sensor into the appropriate variable.
void TiltyIMU::updateSensors()
{
	imu_updated = false;
	altimeter_updated = false;
	compass_updated = false;
	
	if (hasIMU)
	{
		byte status = imu.getIntStatus();
		//Serial.println(status, HEX);
		if (status & 0x13)// Used to be 0x12, but new data register is 0x01, so set to 0x13 to meet both conditions 
		{
			readIMU(status);
			imu_updated = true;
		}
	}
	
	if (hasAlt)
	{
		if (alt.getDataReady()) 
		{
			alt.readAltitudeM(&altimeter_data);
			alt.readTempC(&altimeter_temp);
			altimeter_updated = true;
		}
	}
	
	if (hasMagn)
	{
		if (magn.getDataReady())
		{
			magn.getValues(raw_compass_data);
			compass_updated = true;
		}
	}
}


// Reads data from the IMU sensor
bool TiltyIMU::readIMU(byte imuIntStatus)
{
#ifdef USE_DMP
	// get current FIFO count
	fifoCount = imu.getFIFOCount();
	
	// check for overflow (this should never happen unless our code is too inefficient)
	if ((imuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		imu.resetFIFO();
		#ifdef DEBUG_IMU
			myPort.println(F("FIFO overflow!"));
		#endif
		return false;

	// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (imuIntStatus & 0x03) {// used to sometimes work with 0x01, sometimes 0x02. Set to 0x03 to meet both conditions
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

		// read a packet from FIFO
		imu.getFIFOBytes(fifoBuffer, packetSize);
		
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;
	}
	
	return true;
#endif
}


// Uses data read from the IMU sensor to calculate yaw, pitch, and roll
void TiltyIMU::readAngles(float *data)
{
#ifdef USE_DMP
	imu.dmpGetQuaternion(&q, fifoBuffer);
	imu.dmpGetGravity(&gravity, &q);
	imu.dmpGetYawPitchRoll(data, &q, &gravity);
	data[0] *= 180/M_PI;
	data[1] *= 180/M_PI;
	data[2] *= 180/M_PI;
#endif
}


// Uses data read from the IMU sensor to calculate yaw, pitch, and roll in radians
void TiltyIMU::readAnglesRadians(float *data)
{
#ifdef USE_DMP
	imu.dmpGetQuaternion(&q, fifoBuffer);
	imu.dmpGetGravity(&gravity, &q);
	imu.dmpGetYawPitchRoll(data, &q, &gravity);
#endif
}


// Uses data read from the IMU sensor to determine acceleration relative to gravity, in m/s^2
void TiltyIMU::readNormalAccelerations(float *data)
{
#ifdef USE_DMP
	imu.dmpGetQuaternion(&q, fifoBuffer);
	imu.dmpGetAccel(&aa, fifoBuffer);
	imu.dmpGetGravity(&gravity, &q);
	imu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
	imu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
	
	data[0] = 9.81 * (aaWorld.x / 8192.0);
	data[1] = 9.81 * (aaWorld.y / 8192.0);
	data[2] = 9.81 * (aaWorld.z / 8192.0);
#endif
}


// Returns the raw gyro data
void TiltyIMU::getRawGyro(int *data)
{
	data[0] = int16_t((fifoBuffer[16] << 8) | fifoBuffer[17]);
	data[1] = int16_t((fifoBuffer[20] << 8) | fifoBuffer[21]);
	data[2] = int16_t((fifoBuffer[24] << 8) | fifoBuffer[25]);
}


// Returns the raw accelerometer data
void TiltyIMU::getRawAccel(int *data)
{
	data[0] = int16_t((fifoBuffer[28] << 8) | fifoBuffer[29]);
	data[1] = int16_t((fifoBuffer[32] << 8) | fifoBuffer[33]);
	data[2] = int16_t((fifoBuffer[36] << 8) | fifoBuffer[37]);
}


// Reads the altitude from the altimeter sensor
float TiltyIMU::readAltitude(float *data)
{
	if (alt.getDataReady())
	{
		*data = alt.readAltitudeM();
		return *data;
	}
	else
	{
		return 0;
	}
}

/** \brief Reads the voltage on the Tilty's power inputs
	
	\param[in] *data Pointer to the voltage variable
	\param[out] Voltage
**/
void TiltyIMU::readVoltage(float *data)
{
	*data = analogRead(VOLTAGE_SENSE_PIN) * VOLTAGE_DIVIDER;
}


float TiltyIMU::readVoltage()
{
	return analogRead(VOLTAGE_SENSE_PIN) * VOLTAGE_DIVIDER;
}




