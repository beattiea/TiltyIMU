#include <I2Cdev.h>
//#include <MPU6050.h>
#include <EEPROM.h>

#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;

//#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
//#include <Wire.h> // Uncomment to use standard Wire library on normal Arduinos
#include <i2c_t3.h> // Uncomment to use I2C_t3 Wire library on Teensy 3.0
#include <SPI.h>

#include "FastServo.h"

#define GO_PIN 2
#define STEER_PIN 3
#define STEER_SENSE 23

#define STEER_CENTER 373

FreeIMU imu = FreeIMU();	// Simple sensor fusion IMU object
float ypr[3];				// Simple sensor fusion IMY yaw, pitch, and roll values.
float old_ypr[3];			// Previous sensor readings, used for derivative PID calculation
const short YAW = 0;		// Yaw position in ypr[]
const short PITCH = 1;		// Pitch position in ypr[]
const short ROLL = 2;		// Roll position in ypr[]

Servo go_servo;
Servo turn_servo;

float kP = 25.0;		// Proportional PID gain
float kI = 0.25;			// Integral PID gain
float kD = 5.0;		// Derivative PID gain
float P, I, D;			// PID values

int S = 255;

const int MAX_STARTING_PITCH = 3; // Maximum pitch before segwoid will begin balancing (must be < this and > -this)
const int MAX_RUNNING_PITCH = 20; // Maximum pitch before segwoid stops running code and waits to be back in starting pitch range

void setup() {
	Serial.begin(115200);
	
	go_servo.attach(GO_PIN);
	turn_servo.attach(STEER_PIN);
	
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	
	delay(5);
	
	imu.init();
	//setupDMP();
	
	delay(5);
	
	for (int i = 0; i < 200; i++) {
		readIMU();
		delay(10);
	}
	/*
	while (!Serial) { // wait for a serial connection just for debugging purposes
		readIMU();
		delay(10);
	}
	*/
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	
	short count;
	while (true) {
		float std_dev[255];
		for (int i = 0; i < 255; i++) {
			readIMU();
			std_dev[i] = ypr[PITCH];
			delay(5);
		}
		float val = standardDev(std_dev, 100);
		Serial.print("Standard Deviation: ");
		Serial.println(val, 3);
		if (val < 0.125) {
			count++;
			if (count > 3) {
				digitalWrite(13, LOW);
				break;
			}
		}
		else {	count = 0;}
	}
	
	imu.zeroGyro();
}

void loop() {
	if (abs(ypr[PITCH]) < MAX_STARTING_PITCH) {		// Check to see if segwoid is in a balanced position before starting
		digitalWrite(13, HIGH);
		while (abs(S) > 5 && abs(ypr[PITCH]) < MAX_STARTING_PITCH) {
			readIMU();
			updatePID();
			P /= 5;
			I /= 5;
			D /= 5;
			writeServos(P + I + D, 0);
			printDebugValues();
			delay(10);
		}
		resetPID();
		while (abs(ypr[PITCH]) < MAX_RUNNING_PITCH) {	// Code to run while segwoid is stable
			readIMU();
			updatePID();
			printDebugValues();
			
			writeServos(P + I + D, S / 2.5);
			//writeServos(0, S / 2.5);
			
			//delay(10);
		}
	}
	else resetPID();
	
	digitalWrite(13, LOW);
	readIMU();
	writeServos(0, 0);
	printDebugValues();
	
	delay(10);
}

void readIMU() {
	for (int i = 0; i < 3; i++) {	old_ypr[i] = ypr[i];} // Save the old ypr values
	imu.getEuler(ypr); // read new ypr values
}

void printDebugValues() {
	Serial.print("Yaw: ");
	Serial.print(ypr[0]);
	Serial.print(" \tPitch: ");
	Serial.print(ypr[1]);
	Serial.print(" \tRoll: ");
	Serial.print(ypr[2]);
	
	Serial.print("\t\tSteer: ");
	Serial.print(analogRead(STEER_SENSE));
	
	Serial.print("\t\tP: ");
	Serial.print(P);
	Serial.print("\tI: ");
	Serial.print(I);
	Serial.print("\tD: ");
	Serial.print(D);
	
	Serial.println();
}

float standardDev(float *vals, size_t size) {
	float mean1, mean2;
	float sum, diff[size];
	
	for (int i = 0; i < size; i++)	sum += vals[0];
	mean1 = sum / size;
	for (int i = 0; i < size; i++)	diff[i] = pow((vals[i] - mean1), 2);
	sum = 0;
	for (int i = 0; i < size; i++) sum += diff[i];
	return (sum / size);
	
	
}