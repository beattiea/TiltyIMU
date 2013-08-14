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


//	Setting defines
//#define DEBUG
#define USE_DMP
#define USE_FAST_SERVO


#include "Arduino.h"
//#include "TiltyIMU.h"

//	I2C library
#include <i2c_t3.h>

//	Servo libraries
#ifdef USE_FAST_SERVO
	#include <FastServo.h>
#else
	#include <Servo.h>
#endif

// MPU-6050 IMU libraries
#include <I2Cdev.h>
#ifdef USE_DMP
	#include <MPU6050_6Axis_MotionApps20.h>
#else
	#include <MPU6050.h>
#endif

//	Altimeter library
#include <MPL3115A2.h>

//	Compass library
#include <HMC5883.h>


class TiltyIMU {
	public:
	// Class constructors
		TiltyIMU();
		~TiltyIMU();
	// Sensor declarations
		MPU6050 imu; // IMU motion sensor
		HMC5883 magn; // Compass sensor
		MPL3115A2 alt; // Altitude/pressure sensor
	
	// Sensor initializers
		void init();
	
	private:
	// Sensor initializations
		
		bool hasIMU;
		bool hasMagn;
		bool hasAlt;
		
		//	Debug defines
		#ifdef DEBUG
			#define DEBUG_PRINT(x) Serial.print(x)
			#define DEBUG_PRINTF(x, y) Serial.print(x, y)
			#define DEBUG_PRINTLN(x) Serial.println(x)
			#define DEBUG_PRINTLNF(x, y) Serial.println(x, y)
		#else
			#define DEBUG_PRINT(x)
			#define DEBUG_PRINTF(x, y)
			#define DEBUG_PRINTLN(x)
			#define DEBUG_PRINTLNF(x, y)
		#endif
};




#endif