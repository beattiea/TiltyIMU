#ifndef RCadapter_h
#define RCadapter_h

#include "Arduino.h"

#ifdef CORE_TEENSY && __arm__
// Teensy class data
#include <i2c_t3.h>

#ifndef I2C_ADDRESS
	char I2C_ADDRESS = 0x02;
#endif

// End Teensy/Master class information

#else

// Add-on/shield class information
#include "Wire.h"
#include "EEPROM.h"

//#define FAST_SERVO
#ifdef FAST_SERVO
	#include "FastServo.h"
#else
	#include "Servo.h"
#endif

#define USE_SATELLITE_RX // Non-removable for now
#ifdef USE_SATELLITE_RX
	#include "SatelliteRX.h"
#endif

#define BUFFER_SIZE 14

// EEPROM data addresses
#define I2C_EEPROM_ADDRESS 0
#define SAT_RX_BOUND_ADDRESS 1

class RCadapter {
	public:
		// Constructors
		RCadapter();
		~RCadapter();
		
		// Satellite RX object
		SatelliteRX satRX;
		
		// Initialization functions
		boolean init();
		
		void initServo(Servo &servo, char servo_pin);
		void initServo(char servo);
		
		// Read signal functions
		bool readSatRX();
		
		// write servo functions
		int writeServo(char servo, int value);
		int writeServo(Servo &servo, int value);
	
	private:
		// I2C data buffer
		char buffer[BUFFER_SIZE];
		
		int servo_trims[6]; // Trim values for individual servos NOT IMPLEMENTED
		
		Servo servo_1;
		Servo servo_2;
		Servo servo_3;
		Servo servo_4;
		Servo servo_5;
		Servo servo_6;
		
	
};
// End add-on class information
#endif
#endif