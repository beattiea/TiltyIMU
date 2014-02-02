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

#define DEBUG_MOTOR_DRIVER
#ifdef DEBUG_MOTOR_DRIVER
	#define m1_power 100
	#define m1_p 101
	#define m1_i 102
	#define m1_d 103
	#define m2_power 104
	#define m2_p 105
	#define m2_i 106
	#define m2_d 107
	#define pid_kp 108
	#define pid_ki 109
	#define pid_kd 110
	#define led	111
	#define eeprom 200
#endif


// ========== I2C Settings ==========
#define REGISTER_SIZE 45
#define BUFFER_SIZE 32
#define DEFAULT_MOTOR_DRIVER_I2C_ADDRESS 0x03
// ========== I2C Settings ==========


//==========================================================================================//
// Add-on/shield class information

// ========== Library includes ==========
#include "Wire.h"
#include "EEPROM.h"
#include "Encoder.h"
// ========== Library includes ==========

// ========== Motor control pins ==========
// Motor PWM pins
#define M1 6
#define M2 5
// Motor direction control pins
#define M1A 4
#define M1B 9
#define M2A 7
#define M2B 8
#define M1A_PORT 0x08 // Port D
#define M1B_PORT 0x02 // Port B
#define M2A_PORT 0x40 // Port D
#define M2B_PORT 0x01 // Port B
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

// ========== LED pin ==========
#define LED 10
// ========== LED pin ==========

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

// ========== Default Register Values ==========
#define DEFAULT_M1_CONTROL		DIRECTION | BRAKE | ENCODER | SPEED
#define DEFAULT_M2_CONTROL		DIRECTION | BRAKE | ENCODER | SPEED
#define DEFAULT_M1_POWER		0
#define DEFAULT_M2_POWER		0
#define DEFAULT_M1_ENCODER		0
#define DEFAULT_M2_ENCODER		0
#define DEFAULT_M1_CURRENT		0
#define DEFAULT_M2_CURRENT		0
#define DEFAULT_M1_RATE			0
#define DEFAULT_M2_RATE			0
#define DEFAULT_PID_KP			0.33
#define DEFAULT_PID_KI			0.05
#define DEFAULT_PID_KD			0.0
#define DEFAULT_MIN_POWER		75
#define DEFAULT_TICKS_REV		1336
#define DEFAULT_LOOP_TIME		5
#define DEFAULT_DEVICE_ID		0x03
#define DEFAULT_EEPROM_SAVE		0
#define DEFAULT_EEPROM_LOAD		0
// ========== Default Register Values ==========


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
		uint8_t getData(int bytes);
		void sendData();
		
		// Update functions
		int update();
		
		// Motor control functions
		void updateMotor1();
		void updateMotor2();
		
		void updateM1Encoder();
		void updateM2Encoder();
		
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
		uint8_t M1_current;
		uint8_t M2_current;
		float PID_kP;
		float PID_kI;
		float PID_kD;
		long ticks_rev;
		float PID_P1, PID_P2;
		float PID_I1, PID_I2;
		float PID_D1, PID_D2;
		float loop_frequency;
		
		// I2C register data
		uint8_t data_reg[REGISTER_SIZE];
		uint8_t active_reg;
		
		// I2C register addresses
		// Read/Write registers
		//                   Register Name			   Register description			Value Type	 	Register range	
		static const uint8_t M1_CONTROL = 0x00;		// Motor control settings		Byte			0
		static const uint8_t M2_CONTROL = 0x01;		// Motor control settings		Byte			1
		static const uint8_t M1_POWER = 0x02;		// Raw PWM duty cycle			Byte			2
		static const uint8_t M2_POWER = 0x03;		// Raw PWM duty cycle			Byte			3
		static const uint8_t M1_ENCODER = 0x04;		// Raw encoder values			Long			4-7
		static const uint8_t M2_ENCODER = 0x08;		// Raw encoder values			Long			8-11
		static const uint8_t M1_CURRENT = 0x0C;		// Motor current draw/limit		Byte			12	
		static const uint8_t M2_CURRENT = 0x0D;		// Motor current draw/limit		Byte			13
		static const uint8_t M1_RATE = 0x0E;		// Rotation Rate control		Float			14-17
		static const uint8_t M2_RATE = 0x12;		// Rotation Rate control		Float			18-21
		static const uint8_t PID_KP = 0x16;			// PID P scalar					Float			22-25
		static const uint8_t PID_KI = 0x1A;			// PID I scalar					Float			26-29
		static const uint8_t PID_KD = 0x1E;			// PID D scalar					Float			30-33
		static const uint8_t MIN_POWER = 0x22;		// Minimum PWM to turn motor	Byte			34
		static const uint8_t TICKS_REV = 0x23;		// Encoder ticks revolution		Long			35-38
		static const uint8_t LOOP_TIME = 0x27;		// Ms between motor updates		Byte			39
		static const uint8_t DEVICE_ID = 0x28;		// I2C device address			7-bit byte		40
		static const uint8_t EEPROM_SAVE = 0x29;	// Save register to EEPROM		Integer			41-42
		static const uint8_t EEPROM_LOAD = 0x2C;	// Load register from EEPROM	Integer			43-44
	

	#ifdef DEBUG_MOTOR_DRIVER
		uint8_t write32(float val);
	#endif

	private:
		// Data register handling functions
		uint8_t intToDataReg(uint8_t reg, uint16_t value);
		uint8_t longToDataReg(uint8_t reg, uint32_t value);
		uint8_t floatToDataReg(uint8_t reg, float value);
		
		uint8_t wireToDataReg(uint8_t reg, uint8_t bytes);
		uint8_t wireIntToDataReg(uint8_t reg);
		uint8_t wire3BytesToDataReg(uint8_t reg);
		uint8_t wireLongToDataReg(uint8_t reg);
		
		uint16_t intFromDataReg(uint8_t reg);
		uint32_t longFromDataReg(uint8_t reg);
		float 	 floatFromDataReg(uint8_t reg);
		
		// EEPROM functions
		uint16_t loadInt(uint16_t address);
		uint32_t loadLong(uint16_t address);
		uint8_t	 loadIntoRegister(uint16_t address, uint8_t reg, uint8_t bytes);
		uint8_t  loadDataRegister();
		
		uint8_t saveInt(uint16_t address, uint32_t value);
		uint8_t saveLong(uint16_t address, uint32_t value);
		uint8_t saveFromRegister(uint16_t address, uint8_t reg, uint8_t bytes);
		uint8_t saveDataRegister();
		
		// Data union for transferring different 4 byte types to/from data register
		union data_union {
			uint8_t bytes[4];
			uint32_t int32;
			float float32;
		} data_union;
		
		// Counter variable for timing
		uint8_t count;
		
		// Actual motor speeds used to calculate PID for speed control
		volatile float M1_speed_actual;
		volatile float M2_speed_actual;
		
		// Motor control register bit values
		static const uint8_t DIRECTION = 0x01;// Sets motor direction.
		static const uint8_t BRAKE = 0x02;// Motor brake/cost. 1 brakes, 0 coasts.
		static const uint8_t SPEED = 0x04;// Speed/Power control setting. 0 is power, 1 is speed (RPM).
		static const uint8_t ENCODER = 0x08;// Sets whether to enable the encoder
		static const uint8_t ENCD = 0x10;// Set to 1 when new encoder data is available
		static const uint8_t CURD = 0x20;// Set to 1 when new current sense data is available
};
#endif