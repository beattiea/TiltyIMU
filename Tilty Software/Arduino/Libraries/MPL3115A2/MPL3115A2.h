/*
MPL3115A2.h - A easy to use interface for the MPL3115A2 Altimeter from Freescale Semiconductor
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

/*
This is a library to control and read a MPL3115A2 Altimeter from Freescale Semiconductor
*/

// ensure this library description is only included once
#ifndef MPL3115A2_h
#define MPL3115A2_h

//#define DEBUG

#include <i2c_t3.h>
#include "WProgram.h"
#include "Arduino.h"

#define _addr 0x60//	Sensor I2C address
#define std_temp 20//	Standard temperature at sea level
#define std_press 101326//	Standard pressure at sea level

class MPL3115A2 {
	public:
		//	Constructors:
		MPL3115A2();
		~MPL3115A2();
		
		//	Initialization functions
		boolean init();
		
		//	Sensor configuration functions
		void reset();
		void setOversampling(uint8_t _oversample);
		
		//	Check for data functions
		bool getDataReady();
		
		//	Read data functions
		float readAltitudeM();
		float readAltitudeF();
		
		float readTempC();
		float readTempF();
		
		void forceMeasurement();
		
	private:
		//	I2C read/write functions
		byte readByte(byte _regAddr);// Read a single byte from a given register
		byte writeByte(byte _regAddr, byte _value);// Writes a given byte to a given register
		void readBytes(byte _regAddr, uint8_t _length, uint8_t *buffer);// Reads a given number of bytes sequentially from a given initial register to a given buffer array
		
		//	Private variables
		uint8_t _buffer[5];
};

#endif