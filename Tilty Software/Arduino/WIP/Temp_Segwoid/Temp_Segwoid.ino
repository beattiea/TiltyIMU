#include <I2Cdev.h>
#include <MPU6050.h>
#include <EEPROM.h>

//#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
//#include <Wire.h> // Uncomment to use standard Wire library on normal Arduinos
#include <i2c_t3.h> // Uncomment to use I2C_t3 Wire library on Teensy 3.0
#include <SPI.h>

#include "FastServo.h"

#include "DualMotorDriver.h"


FreeIMU imu = FreeIMU();	// Simple sensor fusion IMU object
float ypr[3];				// Simple sensor fusion IMY yaw, pitch, and roll values.
float old_ypr[3];			// Previous sensor readings, used for derivative PID calculation
const short YAW = 0;		// Yaw position in ypr[]
const short PITCH = 1;		// Pitch position in ypr[]
const short ROLL = 2;		// Roll position in ypr[]

Servo go_servo;
Servo turn_servo;

float kP = 0.0;		// Proportional PID gain
float kI = 0.0;	// Integral PID gain
float kD = 0.0;		// Derivative PID gain
float P, I, D;		// PID values

const int MAX_STARTING_PITCH = 3; // Maximum pitch before segwoid will begin balancing (must be < this and > -this)
const int MAX_RUNNING_PITCH = 90; // Maximum pitch before segwoid stops running code and waits to be back in starting pitch range

void setup() {
	Serial.begin(115200);
	
	go_servo.attach(2);
	turn_servo.attach(3);
	
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	
	delay(5);
	
	imu.init();
	
	delay(5);
	
	for (int i = 0; i < 1000; i++) {
		readIMU();
		delay(5);
	}
	
	while (!Serial) { // wait for a serial connection just for debugging purposes
		readIMU();
		delay(10);
	}
}

void loop() {
	if (abs(ypr[PITCH]) < MAX_STARTING_PITCH) {		// Check to see if segwoid is in a balanced position before starting
		while (abs(ypr[PITCH]) < MAX_RUNNING_PITCH) {	// Code to run while segwoid is stable
			readIMU();
			updatePID();
			printDebugValues();
			
			writeServos(P + I + D, 0);
			
			delay(10);
		}
	}
	else resetPID();
	
	readIMU();
	writeServos(0, 0);
	printDebugValues();
	
	delay(10);
}

void readIMU() {
	for (int i = 0; i < 3; i++) {	old_ypr[i] = ypr[i];} // Save the old ypr values
	imu.getYawPitchRoll(ypr); // read new ypr values
}

void printDebugValues() {
	Serial.print("Yaw: ");
	Serial.print(ypr[0]);
	Serial.print(" \tPitch: ");
	Serial.print(ypr[1]);
	Serial.print(" \tRoll: ");
	Serial.print(ypr[2]);
	Serial.print("\t\tP: ");
	Serial.print(P);
	Serial.print("\tI: ");
	Serial.print(I);
	Serial.print("\tD: ");
	Serial.print(D);
	Serial.println();
}