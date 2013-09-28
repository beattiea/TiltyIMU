#include "Arduino.h"
#include "RCadapter.h"

#ifdef CORE_TEENSY && __arm__
// Teensy class data

// End Teensy/Master class information

#else
// Add-on/shield code

#define SERVO_1_PIN 9
#define SERVO_2_PIN 8
#define SERVO_3_PIN 5
#define SERVO_4_PIN 6
#define SERVO_5_PIN 7
#define SERVO_6_PIN 4

RCadapter::RCadapter() : satRX(Serial)
{
	#ifndef I2C_ADDRESS
		char I2C_ADDRESS = EEPROM.read(I2C_EEPROM_ADDRESS);
		if (I2C_ADDRESS == 255)
		{
			I2C_ADDRESS = 0x02;
			EEPROM.write(I2C_EEPROM_ADDRESS, I2C_ADDRESS);
		}
	#endif
	TWBR = 400000L;// Set up I2C for 400kHz
	Wire.begin(I2C_ADDRESS); // Begin I2C at slave address I2C_ADDRESS (defaults to 0x02)
	satRX.init(); // setup satellite receiver
}

RCadapter::~RCadapter() 
{
	// Do nothing
}



/** \brief Call this function before using a servo to initialize 
	\param[in] servo A Servo object to initialize
	\param[in] servo_pin The pin the servo is attached to (ex: SERVO_1_PIN, SERVO_2_PIN, etc.)
**/
void RCadapter::initServo(Servo &servo, char servo_pin) 
{
	servo.attach(servo_pin);
}

/** \brief Call this function before using a servo to initialize 
	\param[in] servo Servo connection number (1-6)
**/
void RCadapter::initServo(char servo) 
{
	switch (servo) {
		case 1: servo_1.attach(SERVO_1_PIN); break;
		case 2: servo_2.attach(SERVO_2_PIN); break;
		case 3: servo_3.attach(SERVO_3_PIN); break;
		case 4: servo_4.attach(SERVO_4_PIN); break;
		case 5: servo_5.attach(SERVO_5_PIN); break;
		case 6: servo_6.attach(SERVO_6_PIN); break;
	}
}



/** \brief Checks to see if Satellite receiver has uploaded new data
	\param[out] boolean Returns true if new data has been read, false if data isn't ready yet
**/
bool RCadapter::readSatRX()
{
	return satRX.readData();
}



/** \brief Writes a value to one of the servo headers to control a servo or electronic speed dontroller
	\param[in] servo A servo object to write to
	\param[in] value Value from -500 to 500 representing the full range of the servo or ESC
	\param[out] boolean Returns 1 if servo successfulyy written, or 0 if servo is not initialized
**/
int RCadapter::writeServo(Servo &servo, int value)
{
	if (!servo.attached()) { return 0;}
	servo.writeMicroseconds(value);
	return 1;
}

/** \brief Writes a value to one of the servo headers to control a servo or electronic speed dontroller
	\param[in] servo Servo connection number (1-6)
	\param[in] value Value from -500 to 500 representing the full range of the servo or ESC
	\param[out] boolean Returns 1 if servo successfulyy written, or 0 if servo is not initialized
**/
int RCadapter::writeServo(char servo, int value) 
{
	value = map(value, -500, 500, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	switch (servo) {
		case 1: return writeServo(servo_1, value); break;
		case 2: return writeServo(servo_2, value); break;
		case 3: return writeServo(servo_3, value); break;
		case 4: return writeServo(servo_4, value); break;
		case 5: return writeServo(servo_5, value); break;
		case 6: return writeServo(servo_6, value); break;
	}
}

// End add-on class information
#endif