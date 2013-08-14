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
	// Do nothing yet
}


void TiltyIMU::init()
{
	hasIMU = imu.init();
	hasMagn = magn.init();
	hasAlt = alt.init();
	
	if (hasIMU)
	{
		imu.dmpInitialize();
	}
}