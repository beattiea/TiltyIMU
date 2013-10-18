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
#define REGISTER_SIZE 12
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

#define LED 10

// ========== Command identifiers ==========

// ========== Command identifiers ==========


class MotorDriver {
	public:
		// Constructors
		MotorDriver();
		~MotorDriver();
		
		// Encoder objects
		Encoder m1Encoder;
		Encoder m2Encoder;
		
		// Initialization functions
		void init();
		
		// I2C data handlers
		int getData(int bytes);
		int sendData();
		
		// Update functions
		int update();
		
		// Motor status variables
		uint8_t M1_control;
		uint8_t M2_control;
		uint8_t M1_power;
		uint8_t M2_power;
		volatile int32_t M1_encoder;
		volatile int32_t M2_encoder;
		
		// I2C register data
		uint8_t data_reg[REGISTER_SIZE];
		uint8_t active_reg;
		
		// I2C register addresses
		static const uint8_t M1_CONTROL = 0x00;
		static const uint8_t M2_CONTROL = 0x01;
		static const uint8_t M1_POWER = 0x02;
		static const uint8_t M2_POWER = 0x03;
		static const uint8_t M1_ENCODER = 0x04;
		static const uint8_t M2_ENCODER = 0x09;

	private:
		// Motor control functions
		void updateMotor1();
		void updateMotor2();
		
		void updateEnc1Reg();
		void updateEnc2Reg();
		
		// Encoder union variable for converting 32 bit integer to byte array
		union enc_union {
			uint8_t bytes[4];
			int32_t int32;
		} enc_union;
		
		// Motor control register bit values
		static const uint8_t DIRECTION = 0x01;// Sets motor direction.
		static const uint8_t BRAKE = 0x02;// Motor brake/cost. 1 brakes, 0 coasts.
		static const uint8_t SPEED = 0x04;// Speed/Power control setting. 0 is power, 1 is speed (RPM).
		static const uint8_t INVERT = 0x08;// Motor direction inversion. 0 is normal, 1 is inverted.
		static const uint8_t EN_ENC = 0x10;// Sets whether to enable the encoder
	
};
// End add-on class information
//==========================================================================================//
#endif
#endif