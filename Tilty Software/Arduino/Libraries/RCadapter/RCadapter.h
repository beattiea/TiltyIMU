/*
RCadapter.h - Software library to program and control the TiltyIMU DR/C Receiver Adapter Shield
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

#ifndef RCadapter_h
#define RCadapter_h

#include "Arduino.h"

#ifdef CORE_TEENSY && __arm__
//==========================================================================================//
// Teensy class data
#include <i2c_t3.h>

#ifndef RC_I2C_ADDRESS
	char I2C_ADDRESS = 0x02;
#endif

// End Teensy/Master class information
//==========================================================================================//
#else
//==========================================================================================//
// Add-on/shield class information
#include "Wire.h"
#include "EEPROM.h"

#define MAX_INPUTS 12
#define MAX_OUTPUTS 12

//#define FAST_SERVO
#ifdef FAST_SERVO
	#include "FastServo.h"
#else
	#include "Servo.h"
#endif

#include "SatelliteRX.h"	
#define SATELLITE_RX_TIMEOUT 100 // Satellite RX connection is assumed lost after SATELLITE_RX_TIMEOUT milliseconds
// Satellite Rx readData() error codes
#define NO_NEW_SAT_RX_DATA 0
#define NEW_SAT_RX_DATA 1
#define NO_SAT_RX_CONNECTION 2

// ========== I2C Settings ==========
#define RC_ADAPTER_RX_BUFFER_SIZE 14
#define RC_ADAPTER_TX_BUFFER_SIZE 14
#define DEFAULT_RC_ADAPTER_I2C_ADDRESS 0x02
// ========== I2C Settings ==========

// EEPROM data addresses
#define RC_ADAPTER_I2C_EEPROM_ADDRESS 0
#define USE_SAT_RX_ADDRESS 1 // Boolean whether to initialize the Satellite receiver at startup
#define INPUT_PINS_ADDRESS 2 // Pins last used for input, if not set manually. 12 bytes.
#define OUTPUT_PINS_ADDRESS 14 // Pins last used for output, if not set manually. 12 bytes.

// Command identifiers
#define READ_RC_COMMAND 0x00
#define READ_SERVO_COMMAND 0x40 // 0xC0
#define WRITE_COMMAND 0x80 // 0x80
#define SETTING_COMMAND 0xC0 // 0x40

class RCadapter {
	public:
		// Constructors
		RCadapter();
		~RCadapter();
		
		// Satellite RX object
		SatelliteRX satRX;
		
		// Initialization functions
		void init();
		void initServo(Servo &servo, char servo_pin);
		void initServo(char servo);
		void initSatelliteRX();
		void initRCinputs(uint8_t *pins, uint8_t length);
		
		int getData(int bytes);
		int parseCommand();
		
		// Read signal functions
		int readSatRX();
		int readRCinputs();
		
		// write servo functions
		int writeServo(char servo, int value);
		int writeServo(Servo &servo, int value);
		
	private:
		// R/C channel inputs
		uint8_t input_pins[MAX_INPUTS]; // pins to read
		uint8_t ordered_pins[MAX_INPUTS]; // pins ordered to read correct channel in correct order
		uint32_t last_read; // time of last input reading
		uint8_t input_index; // Index of next input pin to read for getting input order
		uint8_t number_inputs; // contains the number of initialized inputs
		uint32_t rc_start[MAX_INPUTS];
		uint32_t rc_end[MAX_INPUTS];
		uint16_t channel_values[MAX_INPUTS];
		
		// Input min/max values
		uint16_t channel_min[MAX_INPUTS];
		uint16_t channel_max[MAX_INPUTS];
		
		// Servo pwm output pins
		uint8_t output_pins[MAX_OUTPUTS];
		
		// I2C data buffers
		uint8_t rxBuffer[RC_ADAPTER_RX_BUFFER_SIZE];
		uint8_t txBuffer[RC_ADAPTER_TX_BUFFER_SIZE];
		
		// I2C data buffer indexes
		uint8_t rxBufferIndex;
		uint8_t txbufferIndex;
		
		int syncRCinputs();
		int getInputOrder();
		bool inOrderedPins(uint8_t num);
		
		int parseServoWrite();
		
		int servo_trims[6]; // Trim values for individual servos NOT IMPLEMENTED
		
		Servo servo_1;
		Servo servo_2;
		Servo servo_3;
		Servo servo_4;
		Servo servo_5;
		Servo servo_6;
		
		// Satellite RX variables
		unsigned long last_data_timer;
	
};
// End add-on class information
//==========================================================================================//
#endif
#endif