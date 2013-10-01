/*
DualMotorDriver.h - Software library to program and control the TiltyIMU Dual Motor Driver Shield
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

#ifndef DualMotorDriver_h
#define DualMotorDriver_h

#include "Arduino.h"

#ifdef CORE_TEENSY && __arm__
//==========================================================================================//
// Teensy class data
#include <i2c_t3.h>

#ifndef MOTOR_DRIVER_I2C_ADDRESS
	#define DEFAULT_MOTOR_DRIVER_I2C_ADDRESS 0x03
	char I2C_ADDRESS = 0x03;
#endif

// End Teensy/Master class information
//==========================================================================================//
#else
//==========================================================================================//
// Add-on/shield class information

// ========== Library includes ==========
#include "Wire.h"
#include "EEPROM.h"
#ifndef NO_ENCODERS
	#include "Encoder.h"
#endif
// ========== Library includes ==========

// ========== I2C Settings ==========
#define BUFFER_SIZE 14
#define DEFAULT_MOTOR_DRIVER_I2C_ADDRESS 0x03
// ========== I2C Settings ==========

// ========== EEPROM data addresses ==========
#define MOTOR_DRIVER_I2C_EEPROM_ADDRESS 0
// ========== EEPROM data addresses ==========

// ========== Motor control pins ==========
// Motor PWM pins
#define M1 6
#define M2 5
// Motor direction control pins
#define M1A 4
#define M1B 9
#define M2A 7
#define M2B 8
// ========== Motor control pins ==========

// ========== Encoder pins ==========
#define ENC1A 2 // Interrupt pin
#define ENC1B A1
#define ENC2A A0
#define ENC2B 3 // Interrupt pin
// ========== Encoder pins ==========

// ========== Command identifiers ==========

// ========== Command identifiers ==========


class MotorDriver {
	public:
		// Constructors
		MotorDriver();
		~MotorDriver();
		
	#ifndef NO_ENCODERS
		Encoder m1Encoder;
		Encoder m2Encoder;
	#endif
		
		// Initialization functions
		void init();
		
		int getData(int bytes);
		int parseCommand(int bytes);

	private:
		// I2C data buffers
		char rxBuffer[BUFFER_SIZE];
		char txBuffer[BUFFER_SIZE];
	
};
// End add-on class information
//==========================================================================================//
#endif
#endif