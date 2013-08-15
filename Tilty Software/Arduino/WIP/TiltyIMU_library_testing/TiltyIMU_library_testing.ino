#include <TiltyIMU.h>

#include <i2c_t3.h>
#include <FastServo.h> // Uncomment this line to use Fast Servo library
//#include <Servo.h> // Uncomment this line to use standard Servo library

#include <I2Cdev.h>
//#include <MPU6050_6Axis_MotionApps20.h> // Comment this line if not using DMP angle measurement
#include <MPU6050.h>
#include <MPL3115A2.h>

#include <HMC5883.h>

TiltyIMU tilty;

void setup() {
	tilty.init();
}

void loop() {
	
}