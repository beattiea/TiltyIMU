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


byte TiltyIMU::updateSensors()
{
	long start = micros();
	
	if (hasIMU)
	{
		//Serial.println("Read IMU");
		byte status = imu.getIntStatus();
		if (status & 0x12) 
		{
			readIMU(status);
			//Serial.println("Read IMU");
		}
	}
	
	if (hasAlt)
	{
		if (alt.getDataReady()) 
		{
			alt.readAltitudeM(); 
			//Serial.println("Read Altimeter");
		}
	}
	
	if (hasMagn)
	{
		float data[3];
		if (magn.getDataReady())
		{
			magn.getValues(data);
			//Serial.println("Read Compass");
		}
	}
	
	Serial.println(micros() - start);
}


bool TiltyIMU::readIMU(byte imuIntStatus)
{
	// reset interrupt flag and get INT_STATUS byte
	//bool imuInterrupt = false;
	//bool imuIntStatus = imu.getIntStatus() & 0x12;
	/*
	while (!imuIntStatus) {
		imuIntStatus = imu.getIntStatus() & 0x12;
	}
	*/

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
	} else if (imuIntStatus & 0x01) {
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

		// read a packet from FIFO
		imu.getFIFOBytes(fifoBuffer, packetSize);
		
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;
	}
	
	return true;
}


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


void TiltyIMU::getGyroRates(int *data)
{
	data[0] = int16_t((fifoBuffer[16] << 8) | fifoBuffer[17]);
	data[1] = int16_t((fifoBuffer[20] << 8) | fifoBuffer[21]);
	data[2] = int16_t((fifoBuffer[24] << 8) | fifoBuffer[25]);
}


void TiltyIMU::getAccel(int *data)
{
	data[0] = int16_t((fifoBuffer[28] << 8) | fifoBuffer[29]);
	data[1] = int16_t((fifoBuffer[32] << 8) | fifoBuffer[33]);
	data[2] = int16_t((fifoBuffer[36] << 8) | fifoBuffer[37]);
}


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