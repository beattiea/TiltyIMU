#ifndef RCadapter_h
#define RCadapter_h

#include "Arduino.h"

#ifdef CORE_TEENSY && __arm__
//==========================================================================================//
// Teensy class data
#include <i2c_t3.h>

#ifndef I2C_ADDRESS
	char I2C_ADDRESS = 0x02;
#endif

// End Teensy/Master class information
//==========================================================================================//
#else
//==========================================================================================//
// Add-on/shield class information
#include "Wire.h"
#include "EEPROM.h"

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

#define BUFFER_SIZE 14

// EEPROM data addresses
#define I2C_EEPROM_ADDRESS 0
#define SAT_RX_BOUND_ADDRESS 1

// Command identifiers
#define READ_COMMAND 0b10000000 // 0xC0
#define WRITE_COMMAND 0b01000000 // 0x80
#define SETTING_COMMAND 0b11000000 // 0x40

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
		
		int getData(int bytes);
		int parseCommand(int bytes);
		
		// Read signal functions
		int readSatRX();
		
		// write servo functions
		int writeServo(char servo, int value);
		int writeServo(Servo &servo, int value);
		char rxBuffer[BUFFER_SIZE];
		char txBuffer[BUFFER_SIZE];
	private:
		// I2C data buffer
		
		
		
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