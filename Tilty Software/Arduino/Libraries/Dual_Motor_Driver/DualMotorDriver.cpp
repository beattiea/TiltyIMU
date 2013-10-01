/*
DualMotorDriver.cpp - Software library to program and control the TiltyIMU Dual Motor Driver Shield
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

#include "Arduino.h"
#include "DualMotorDriver.h"

#ifdef CORE_TEENSY && __arm__
// Teensy class data

// End Teensy/Master class information

#else
// Add-on/shield code

MotorDriver::MotorDriver() : m1Encoder(ENC1A, ENC1B), m2Encoder(ENC2B, ENC2A)
{
	
}

MotorDriver::~MotorDriver() 
{
	// Do nothing
}



void MotorDriver::init()
{
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); // Setup pins 5 and 6 for fast PWM
	TCCR0B = _BV(CS00);
	#if PWM_FREQUENCY == 
	#ifndef MOTOR_DRIVER_I2C_ADDRESS
		char I2C_ADDRESS = EEPROM.read(MOTOR_DRIVER_I2C_EEPROM_ADDRESS);
		if (I2C_ADDRESS == 255)
		{
			I2C_ADDRESS = DEFAULT_MOTOR_DRIVER_I2C_ADDRESS;
			EEPROM.write(MOTOR_DRIVER_I2C_EEPROM_ADDRESS, I2C_ADDRESS);
		}
	#else
		I2C_ADDRESS = DEFAULT_MOTOR_DRIVER_I2C_ADDRESS;
	#endif
	TWBR = 400000L;// Set up I2C for 400kHz
	Wire.begin(I2C_ADDRESS); // Begin I2C at slave address I2C_ADDRESS (defaults to 0x02)
}

// End add-on class information
#endif