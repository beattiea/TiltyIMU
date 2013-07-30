/*
MPL3115A2.h - A easy to use interface for the MPL3115A2 Altimeter from Freescale Semiconductor
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
This is a library to control and read a MPL3115A2 Altimeter from Freescale Semiconductor
*/

// ensure this library description is only included once
#ifndef MPL3115A2_h
#define MPL3115A2_h


#include <i2c_t3.h>
#include "WProgram.h"
#include "Arduino.h"

#define _addr 0x60//	Sensor I2C address
#define std_temp 20//	Standard temperature at sea level
#define std_press 101326//	Standard pressure at sea level
#define _timeout 500//	I2C timeout limit in microseconds

class MPL3115A2 {
	public:
		//	Constructors:
		MPL3115A2();
		
		//	Initialization functions
		boolean init();
		
		//	Sensor configuration functions
		void reset();
		
		//	Check for data functions
		boolean checkData();
		
		//	Read data functions
		float readAltitudeM();
		float readAltitudeF();
		
		float readTempC();
		float readTempF();
		
	private:
		//	I2C read/write functions
		byte read(byte _regAddr);
		byte write(byte _regAddr, byte _value);
};

#endif