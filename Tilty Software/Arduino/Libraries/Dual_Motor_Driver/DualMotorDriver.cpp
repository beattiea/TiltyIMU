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
//#ifndef NO_ENCODERS
MotorDriver::MotorDriver()
#ifndef NO_ENCODERS
// Only instantiate encoders if they are allowed to be used
: m1Encoder(ENC1A, ENC1B), m2Encoder(ENC2B, ENC2A)
#endif
{
	uint8_t rxBufferIndex = 0;
	uint8_t tx_bufferIndex = 0;
}

MotorDriver::~MotorDriver() 
{
	// Do nothing
}



void MotorDriver::init()
{
	pinMode(M1, OUTPUT);
	pinMode(M2, OUTPUT);
	
	pinMode(M1A, OUTPUT);
	pinMode(M1B, OUTPUT);
	pinMode(M2A, OUTPUT);
	pinMode(M2B, OUTPUT);
	
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);// Setup pins 5 and 6 for fast PWM
	TCCR0B = _BV(CS00);// Set PWM frequency to 62.5kHz (fastest possible)
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
	Wire.begin(0x03); // Begin I2C at slave address I2C_ADDRESS (defaults to 0x02)
}



/** \brief Takes incoming I2C data into the rxBuffer
	\param[in] bytes The number of incoming bytes
	\param[out] error Returns 0 if buffer overflows, 1 if data is successfully transferred
**/
int MotorDriver::getData(int bytes)
{
	if (bytes > BUFFER_SIZE) { return false;}
	else
	{
		for (int i = 0; i < bytes; i++) { rxBuffer[i] = Wire.read();}
	}
}



/** \brief Parses data in rxBuffer and updates encoder values
**/
int MotorDriver::update()
{
	encoder1 = m1Encoder.read();
	encoder2 = m2Encoder.read();
}

// End add-on class information
#endif