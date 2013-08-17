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

#include "Arduino.h"

#define USE_DMP
#include "MPU6050.h"

#include "MPL3115A2.h"

#include "HMC5883.h"

class TiltyIMU {
	public:
		TiltyIMU();
		void init();
		void readAngles(float *data);
		void initializeIMU();
		void readAltitude(float *data);
		
		bool hasAlt;
		bool hasIMU;
		bool hasMagn;
		
		MPU6050 imu;
		HMC5883 magn;
		MPL3115A2 alt;

		uint16_t packetSize;
		uint16_t fifoCount;
		uint8_t fifoBuffer[64]; // FIFO storage buffer
		Quaternion q;		   // [w, x, y, z]		 quaternion container
		VectorFloat gravity;	// [x, y, z]			gravity vector
};

#endif