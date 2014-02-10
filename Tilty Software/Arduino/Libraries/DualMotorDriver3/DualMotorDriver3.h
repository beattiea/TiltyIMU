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
#define BUFFER_SIZE 32
#define DEFAULT_MOTOR_DRIVER_I2C_ADDRESS 0x03
// ========== I2C Settings ==========


//==========================================================================================//
// Add-on/shield class information

// ========== Library includes ==========
#include "Wire.h"
#include "EEPROM.h"
#include "includes/Encoder.h"
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