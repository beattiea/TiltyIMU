/*
TiltyIMU.h - A easy to use interface for the TiltyIMU line of circuit boards
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

// ensure this library description is only included once
#ifndef TILTYIMU_H
#define TILTYIMU_H

// Setting Defines
#define DEBUG_INITS

#define USE_DMP // Must use this for now, no alternative
#define myPort Serial
#define I2C_RATE I2C_RATE_800

#include "Arduino.h"

// Sensor includes
// IMU files
#include <I2Cdev.h>
#include "Tilty_MPU6050.h"
// Altimeter files
#include "Tilty_MPL3115A2.h"
// Compass files
#include "Tilty_HMC5883.h"

class TiltyIMU {
	public:
		TiltyIMU(void);
		~TiltyIMU();
		
		// Sensor objects
		MPU6050 imu;
		HMC5883 magn;
		MPL3115A2 alt;
		
		// Functionality functions
		void init();
		
		void updateSensors();
		
		bool readIMU(byte imuIntStatus);
		
		// IMU Functions
		void readAngles(float *data);
		void readNormalAccelerations(float *data);
		
		void getRawGyro(int *data);
		void getRawAccel(int *data);
		
		// Altimeter Functions
		float readAltitude(float *data);
		
		// AHRS data
		float ypr[3];
		float altitude;
		
		// Sensor available variables (true means sensor is initialized and available)
		bool hasAlt;
		bool hasIMU;
		bool hasMagn;
		
		// Sensors updated, allows you to keep track of which sensors update in updateSensors()
		bool imu_updated;
		bool altimeter_updated;
		bool compass_updated;
	
	private:
	// IMU stuff
		void initializeIMU();
		
		int16_t x_accel_offset = -4600;
		int16_t y_accel_offset = 709;
		int16_t z_accel_offset = 771;
	
		uint16_t packetSize;
		uint16_t fifoCount;
		uint8_t fifoBuffer[64]; // FIFO storage buffer
		Quaternion q;		   // [w, x, y, z]		 quaternion container
		VectorInt16 aa;		 // [x, y, z]			accel sensor measurements
		VectorInt16 aaReal;	// [x, y, z]			world-frame accel sensor measurements
		VectorInt16 aaWorld;	// [x, y, z]			world-frame accel sensor measurements
		VectorFloat gravity;	// [x, y, z]			gravity vector
		
	// Altimeter stuff
		float raw_altimeter_data;
		float altimeter_temp;
		
	// Compass stuff
		float raw_compass_data[3];
};

#endif