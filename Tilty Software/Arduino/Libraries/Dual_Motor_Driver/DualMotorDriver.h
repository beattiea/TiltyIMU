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

// ========== I2C Settings ==========
#define REGISTER_SIZE 25
#define DEFAULT_MOTOR_DRIVER_I2C_ADDRESS 0x03
// ========== I2C Settings ==========


#ifdef CORE_TEENSY && __arm__
//==========================================================================================//
// Teensy class data
#include <i2c_t3.h>

class MotorDriver {
	public:
		// Constructors
		MotorDriver();
		MotorDriver(uint8_t address);
		~MotorDriver();
		
		// Initialization functions
		int init();
		
		// Motor control functions
		uint8_t setPower(uint8_t motor, uint8_t power);
		uint8_t setPowers(uint8_t power1, uint8_t power2);
		
		uint8_t setPower(uint8_t motor, uint16_t power);
		uint8_t setMotors(int16_t power1, int16_t power2);
		uint8_t setMotor(uint8_t motor, int16_t power);
		
		// I2C address
		uint8_t i2c_address;

		// Motor status variables
		uint8_t M1_control_reg;
		bool M1_direction = true;
		bool M1_brake = false;
		bool M1_control = false;
		bool M1_enc = true;
		
		uint8_t M2_control_reg;
		bool M2_direction = true;
		bool M2_brake = false;
		bool M2_control = false;
		bool M2_enc = true;

		// I2C register data
		uint8_t data_reg[REGISTER_SIZE];
		uint8_t active_reg;

		// I2C register addresses
		// Read/Write registers
		static const uint8_t M1_CONTROL = 0x00;		// Motor control settings
		static const uint8_t M2_CONTROL = 0x01;		// Motor control settings
		static const uint8_t M1_POWER = 0x02;		// Raw PWM duty cycle
		static const uint8_t M2_POWER = 0x03;		// Raw PWM duty cycle
		static const uint8_t M1_ENCODER = 0x04;		// Raw encoder values
		static const uint8_t M2_ENCODER = 0x09;		// Raw encoder values
		static const uint8_t M1_RATE = 0x0D;		// Rotation Rate control
		static const uint8_t M2_RATE = 0x11;		// Rotation Rate control
		static const uint8_t PID_KP = 0x17;
		static const uint8_t PID_KI = 0x18;
		static const uint8_t PID_KD = 0x19;
		// Read only registers
		static const uint8_t M1_CURRENT = 0x15;		// Motor current draw
		static const uint8_t M2_CURRENT = 0x16;		// Motor current draw

	private:
		// Register update function
		uint8_t updateControlReg(bool dir, bool brake, bool cont, bool inv, bool enc);
		
		// Encoder union variable for converting 32 bit integer to byte array
		union enc_union {
			uint8_t bytes[4];
			int32_t int32;
		} enc_union;

		// Motor control register bit values
		static const uint8_t DIRECTION = 0x01;// Sets motor direction.
		static const uint8_t BRAKE = 0x02;// Motor brake/cost. 1 brakes, 0 coasts.
		static const uint8_t SPEED = 0x04;// Speed/Power control setting. 0 is power, 1 is speed (RPM).
		static const uint8_t ENC = 0x08;// Sets whether to enable the encoder
		static const uint8_t ENCD = 0x10;// Set to 1 when new encoder data is available
		static const uint8_t CURD = 0x20;// Set to 1 when new current sense data is available

};

// End Teensy/Master class information
//==========================================================================================//
#else
//==========================================================================================//
// Add-on/shield class information

// ========== Library includes ==========
#include "Wire.h"
#include "EEPROM.h"
#include "Encoder.h"
// ========== Library includes ==========

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
// Motor current sense pins
#define M1_SENSE A2
#define M2_SENSE A3
// ========== Motor control pins ==========

// ========== Encoder pins ==========
#define ENC1A 2 // Interrupt pin
#define ENC1B A1
#define ENC2A A0
#define ENC2B 3 // Interrupt pin
// ========== Encoder pins ==========

// ========== Motor Characteristics ==========
#define TICKS_PER_REV 1336
#define GEAR_RATIO 9.28
#define DEFAULT_KP 1
#define DEFAULT_KI 1
#define DEFAULT_KD 0
// ========== Motor Characteristics ==========

#ifndef REFRESH_FREQ
	#define REFRESH_FREQ 100 // Frequency at which to update encoders and motor powers if in speed control mode
#endif
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
		void sendData();
		
		// Update functions
		int update();
		
		// Motor control functions
		void updateMotor1();
		void updateMotor2();
		
		void updateEnc1Reg();
		void updateEnc2Reg();
		
		void updateMotor1Rate();
		void updateMotor2Rate();
		
		void updateM1Current();
		void updateM2Current();
		
		// Motor status variables
		uint8_t M1_control;
		uint8_t M2_control;
		uint8_t M1_power;
		uint8_t M2_power;
		volatile int32_t M1_encoder;
		volatile int32_t M2_encoder;
		volatile float M1_speed;
		volatile float M2_speed;
		uint8_t M1_current;// Unused
		uint8_t M2_current;// Unused
		uint8_t PID_P1, PID_P2;
		uint8_t PID_I1, PID_I2;
		uint8_t PID_D1, PID_D2;
		
		// I2C register data
		uint8_t data_reg[REGISTER_SIZE];
		uint8_t active_reg;
		
		// I2C register addresses
		// Read/Write registers
		static const uint8_t M1_CONTROL = 0x00;		// Motor control settings
		static const uint8_t M2_CONTROL = 0x01;		// Motor control settings
		static const uint8_t M1_POWER = 0x02;		// Raw PWM duty cycle
		static const uint8_t M2_POWER = 0x03;		// Raw PWM duty cycle
		static const uint8_t M1_ENCODER = 0x04;		// Raw encoder values
		static const uint8_t M2_ENCODER = 0x09;		// Raw encoder values
		static const uint8_t M1_RATE = 0x0D;		// Rotation Rate control
		static const uint8_t M2_RATE = 0x11;		// Rotation Rate control
		static const uint8_t PID_KP = 0x17;
		static const uint8_t PID_KI = 0x18;
		static const uint8_t PID_KD = 0x19;
		// Read only registers
		static const uint8_t M1_CURRENT = 0x15;		// Motor current draw
		static const uint8_t M2_CURRENT = 0x16;		// Motor current draw

	private:
		// Encoder union variable for converting 32 bit integer to byte array
		union enc_union {
			uint8_t bytes[4];
			int32_t int32;
		} enc_union;
		
		// Encoder union variable for cconverting rotations per second to 4 byte array
		union rot_union {
			uint8_t bytes[4];
			float flt;
		} rot_union;
		
		// Actual motor speeds used to calculate PID for speed control
		volatile float M1_speed_actual;
		volatile float M2_speed_actual;
		
		// Motor control register bit values
		static const uint8_t DIRECTION = 0x01;// Sets motor direction.
		static const uint8_t BRAKE = 0x02;// Motor brake/cost. 1 brakes, 0 coasts.
		static const uint8_t SPEED = 0x04;// Speed/Power control setting. 0 is power, 1 is speed (RPM).
		static const uint8_t ENC = 0x08;// Sets whether to enable the encoder
		static const uint8_t ENCD = 0x10;// Set to 1 when new encoder data is available
		static const uint8_t CURD = 0x20;// Set to 1 when new current sense data is available
		
		uint8_t checkReadOnly(uint8_t val);// Checks if a register is read only before allowing it to be written
		uint16_t count;
	
};
// End add-on class information
//==========================================================================================//
#endif
#endif