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
	uint8_t data_reg[REGISTER_SIZE] = {0x12, 0x12, 0x00, 0x00}; // Initializes the status and control register array
}

MotorDriver::~MotorDriver() 
{
	// Do nothing
}




/** \brief Initializes the add-on board (starts Wire, sets up fast PWM, etc...)
**/
void MotorDriver::init()
{
	pinMode(M1, OUTPUT);
	pinMode(M2, OUTPUT);
	
	pinMode(M1A, OUTPUT);
	pinMode(M1B, OUTPUT);
	pinMode(M2A, OUTPUT);
	pinMode(M2B, OUTPUT);
	
	pinMode(LED, OUTPUT);
	
	data_reg[0] = 0x12;
	data_reg[1] = 0x12;
	data_reg[2] = 0xAA;
	data_reg[3] = 0x05;
	
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
	\param[out] error Returns 0 if register overflows, 1 if data is successfully transferred
**/
int MotorDriver::getData(int bytes)
{
	active_reg = Wire.read();
	
	for (char i = 1; i < bytes; i++)
	{
		if (active_reg >= REGISTER_SIZE) {	return 0;}
		
		else
		{
			data_reg[active_reg] = Wire.read();
			active_reg++;
		}
	}
	return 1;
}



/** \brief Sends requested I2C data
	\param[out] error Returns 0 if register overflows, 1 if data is successfully transferred
**/
int MotorDriver::sendData()
{	
	Wire.write(data_reg, 4);
	
	/*
	while (TWSR & 0x08 && active_reg < REGISTER_SIZE)
	{
		Wire.write(data_reg[active_reg]);
		active_reg++;
	}
	*/
}



/** \brief Parses data in rxBuffer and updates encoder values
**/
int MotorDriver::update()
{
	updateMotor1();
	//updateMotor2();
}



/** \brief Updates Motor 1 based on control register bit settings
**/
void MotorDriver::updateMotor1()
{
	uint8_t M1_updates = data_reg[M1_CONTROL] ^ M1_control;// gets a list of what values have changed
	
	if (M1_updates & BRAKE) // If ENABLE bit value has changed, enables/disables the motor
	{
		M1_control ^= BRAKE;
		if (M1_control & BRAKE) // If enabled, sets MxA and MxB both HIGH
		{
			digitalWrite(M1A, HIGH);
			digitalWrite(M1B, HIGH);
			return;
		}
		else // If disabled, sets the motor to DIRECTION
		{
			if (M1_control & INVERT) // If inverted, starts again in inverted direction
			{
				digitalWrite(M1A, !(M1_control & DIRECTION));
				digitalWrite(M1B, (M1_control & DIRECTION));
			}
			else
			{
				digitalWrite(M1A, M1_control & DIRECTION);
				digitalWrite(M1B, !(M1_control & DIRECTION));
			}
		}
	}
	
	// Only checks everything else if BRAKE is not enabled //
	if (!(M1_control & BRAKE))
	{	
		if (M1_updates & DIRECTION) // If DIRECTION bit value has changed, changes motor direction
		{
			M1_control ^= DIRECTION;
			digitalWrite(M1A, !digitalRead(M1A));
			digitalWrite(M1B, !digitalRead(M1B));
		}
	
		if (M1_updates & SPEED) // if SPEED/POWER bit value has changed, changes motor control variable to match
		{
			M1_control ^= SPEED;
		}
	
		if (M1_updates & INVERT)
		{
			M1_control ^= INVERT;
			digitalWrite(M1A, !digitalRead(M1A));
			digitalWrite(M1B, !digitalRead(M1B));
		}
	}
	
	// Updates the motor speed/power values //
	if ((M1_control & SPEED) && !(M1_control & BRAKE)) // If SPEED is enabled and BRAKE is not, uses PID based RPM speed control
	{
		// RPM control PID will go here once implemented and will run every loop regardless of whether the values have changed
	}
	else // If SPEED is LOW or BRAKE is enabled, uses power control from register 0x02 or 0x03 (depends on motor)
	{
		if (M1_power ^ data_reg[M1_POWER]) // Only updates if value has changed
		{
			M1_power = data_reg[M1_POWER];
			analogWrite(M1, M1_power);
		}
	}
	
	if (data_reg[M1_CONTROL] & EN_ENC)
	{
		M1_encoder = m1Encoder.read();
	}
}

// End add-on class information
#endif