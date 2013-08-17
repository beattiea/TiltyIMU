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

/*
TiltyIMU::~TiltyIMU()
{
	// Do nothing yet
}
*/


void TiltyIMU::init()
{
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	delay(5);

	Serial.println("Starting. . .");
	hasIMU = imu.init();
	hasMagn = magn.init();
	hasAlt = alt.init();
	
	Serial.print("Has IMU: ");
	Serial.println(hasIMU);
	Serial.print("Has Altimeter: ");
	Serial.println(hasAlt);
	Serial.print("Has Compass: ");
	Serial.println(hasMagn);
	
	if (hasIMU) initializeIMU();
	
	if (hasMagn) magn.init();
	
	if (hasAlt) alt.init();
}


void TiltyIMU::initializeIMU()
{
#ifdef USE_DMP
	if (!imu.dmpInitialize())
	{
		imu.setDMPEnabled(true);
		packetSize = imu.dmpGetFIFOPacketSize();
	}
#endif
}


void TiltyIMU::readAngles(float *data)
{
#ifdef USE_DMP
	// reset interrupt flag and get INT_STATUS byte
	bool imuInterrupt = false;
	bool imuIntStatus = imu.getIntStatus() & 0x12;
	
	while (!imuIntStatus) {
		imuIntStatus = imu.getIntStatus() & 0x12;
	}

	// get current FIFO count
	fifoCount = imu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((imuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		imu.resetFIFO();
		Serial.println(F("FIFO overflow!"));

	// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (imuIntStatus & 0x01) {
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

		// read a packet from FIFO
		imu.getFIFOBytes(fifoBuffer, packetSize);
		
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;

		imu.dmpGetQuaternion(&q, fifoBuffer);
		imu.dmpGetGravity(&gravity, &q);
		imu.dmpGetYawPitchRoll(data, &q, &gravity);
		data[0] *= 180/M_PI;
		data[1] *= 180/M_PI;
		data[2] *= 180/M_PI;
	}
#endif
}


void TiltyIMU::readAltitude(float *data)
{
	if (alt.getDataReady())
	{
		*data = alt.readAltitudeM();
	}
}