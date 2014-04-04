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

#if defined(__MK20DX128__) || defined(__MK20DX256__)

#include "i2c_t3.h"

// Motor control modes
#define NONE	0
#define MAPPED	0x08
#define SMOOTH	0x04
#define RPM		0x0C

class DualMotorDriver {
	public:
		// Constructors
		DualMotorDriver();
		DualMotorDriver(uint8_t I2C_bus);
		~DualMotorDriver();
		
		void init();
		
		// Device Settings
		uint8_t device_address;
		
		// Motor status/control variables
		uint8_t M1_control;			// Motor 1 control byte
		uint8_t M2_control;			// Motor 2 control byte
		uint8_t M1_power;			// Motor 1 set power value
		uint8_t M2_power;			// Motor 2 set power value
		int32_t M1_encoder;			// Motor 1 current encoder value
		int32_t M2_encoder;			// Motor 2 current encoder value
#if CURRENT_SENSE_SENSITIVITY
		uint16_t M1_current;		// High sensitivity motor 1 current draw (16-bit)
		uint16_t M2_current;		// High sensitivity motor 2 current draw (16-bit)
#else
		uint8_t M1_current;			// Low sensitivity motor 1 current draw (8-bit)
		uint8_t M2_current;			// Low sensitivity motor 2 current draw (8-bit)
#endif
		float M1_rate;				// Current motor rate if encoder is enabled, when written to it updates the target RPM in RPM mode
		float M2_rate;				// Current motor rate if encoder is enabled, when written to it updates the target RPM in RPM mode
		float PID_kP;				// PID P scalar for RPM control
		float PID_kI;				// PID I scalar for RPM control
		float PID_kD;				// PID D scalar for RPM control
		uint8_t min_power;			// Minimum PWM to apply to the motor in all modes except when SPEED and MODE bits are 0
		uint8_t ramping_rate;		// Amount to add/subtract each time ramping code is checked
		
		// Background variables, these are used by the motor driver but the user doesn't need to worry about them
		uint8_t M1_current_power;	// Current power assigned by software, not user editable
		uint8_t M2_current_power;	// Current power assigned by software, not user editable
		uint8_t M1_scaled_power;	// Scaled motor power for minimum PWM control, assigned by software and not user editable
		uint8_t M2_scaled_power;	// Scaled motor power for minimum PWM control, assigned by software and not user editable
		int16_t M1_target_rate;		// Target RPM of motor 1 in RPM mode
		int16_t M2_target_rate;		// Target RPM of motor 2 in RPM mode
		
		typedef struct MotorState {
			uint8_t control;
			uint8_t set_power;
			uint8_t scaled_power;
			uint8_t current_power;
			
#if CURRENT_SENSE_SENSITIVITY
			uint16_t current_draw;	// High sensitivity motor 1 current draw (16-bit)
#else
			uint8_t current_draw;	// Low sensitivity motor 1 current draw (8-bit)
#endif
			
			int16_t target_rate;
			float current_rate;
			
			float PID_P;
			float PID_I;
			float PID_D;
			
			int32_t encoder_value;
		} MotorState;
		
		MotorState motor1;
		MotorState motor2;
		
		void readMotor(uint8_t motor);
		
		void setMotorSpeed(uint8_t motor, uint8_t speed);		// Sets only motor 1 speed
		uint8_t readMotorSpeed(uint8_t motor);
		void setMotorRPM(uint8_t motor, int16_t speed);
		float readMotorRPM(uint8_t motor);
		
		void setPID(float p, float i, float d);
		
	private:
		static const uint8_t DELAY = 150;		// Microsecond delay between reads and writes
		
		// I2C bus switching control
		uint8_t I2C_bus;						// 0 means use pins 18-19, 1 means use pins 16-17
		uint8_t revert;							// Boolean value to indicate if the I2C bus was changed or not
		static const uint16_t I2C_config = 612;	// Core pin config when pin is setup as I2C pin
		static const uint16_t IO_pin = 256;		// Core pin config when pin is setup as general I/O
		inline void setI2Cpins();				// Automatically makes sure Teensy is using the right I2C bus pins
		inline void revertI2Cpins();			// Automatically revert to the previously set I2C pins if necessary
		inline void setI2Cpins1819();			// Setup pins 18 and 19 for use by the I2C bus
		inline void setI2Cpins1617();			// Setup pins 16 and 17 for use by the I2C bus
		
		
		inline void wireToVar(uint8_t *var);
		inline void wireToVar(uint16_t *var);
		inline void wireToVar(int32_t *var);
		inline void wireToVar(float *var);
		
		// Data union for transferring different 4 byte types to/from data register
		union data_union {
			uint8_t bytes[4];
			float float32;
		} data_union;
		
		// Motor control register bit values
		static const uint8_t DIRECTION = 0x01;// Sets motor direction. 0 is forwards, 1 is reverse.
		static const uint8_t BRAKE = 0x02;// Motor brake/cost. 1 brakes, 0 coasts.
		static const uint8_t SPEED = 0x04;// Enables/Disables automatic speed control
		static const uint8_t MODE = 0x08;// Sets speed control type. Ramping power or RPM control
		static const uint8_t ENCODER = 0x10;// Sets whether to enable the encoder
		static const uint8_t CURRENT = 0x20;// Sets whether to read motor currents or not
		static const uint8_t CURD = 0x40;// Set to 1 when new current sense data is available
		//======== Motor control type settings ========
		//	|  SPEED  |  MODE  |  RESULT
		//  |    0    |    0   |  No automatic control, power is written directly to PWM
		//  |    0    |    1   |  No automatic power smoothing, but power is mapped 0%-100% to min_power-255
		//  |    1    |    0   |  Automatic power ramping for smoother transitions between speeds, also mapped min_power-255
		//  |    1    |    1   |  RPM control via the motor rate registers, will automatically enable encoders
		
		// Active variable values, control which variable is modified when an I2C write is performed
		static const uint8_t M1_CONTROL = 0x00;
		static const uint8_t M2_CONTROL = 0x01;
		static const uint8_t M1_POWER = 0x02;
		static const uint8_t M2_POWER = 0x03;
		static const uint8_t M1_CURRENT = 0x04;
		static const uint8_t M2_CURRENT = 0x05;
		static const uint8_t RAMPING_RATE = 0x06;
		static const uint8_t MIN_POWER = 0x07;
		static const uint8_t M1_RATE = 0x08;
		static const uint8_t M2_RATE = 0x09;
		static const uint8_t M1_ENCODER = 0x0A;
		static const uint8_t M2_ENCODER = 0x0B;
		static const uint8_t PID_KP = 0x0C;
		static const uint8_t PID_KI = 0x0D;
		static const uint8_t PID_KD = 0x0E;
		static const uint8_t EEPROM_SAVE = 0x0F;
		static const uint8_t EEPROM_LOAD = 0x10;
		static const uint8_t DEVICE_ADDRESS = 0x20;
		static const uint8_t RESET = 0x30;
		static const uint8_t M1_STATE = 0x31;
		static const uint8_t M2_STATE = 0x32;
};

extern DualMotorDriver MotorDriver;

#endif