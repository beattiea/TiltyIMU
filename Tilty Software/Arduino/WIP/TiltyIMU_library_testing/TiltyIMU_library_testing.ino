
#include <i2c_t3.h>
#include <FastServo.h> // Uncomment this line to use Fast Servo library
//#include <Servo.h> // Uncomment this line to use standard Servo library

#include <I2Cdev.h>
//#include <MPU6050_6Axis_MotionApps20.h> // Comment this line if not using DMP angle measurement
#define MPU6050_INCLUDE_DMP_MOTIONAPPS20
#include <MPU6050.h>
#include <MPL3115A2.h>

#include <HMC5883.h>

#include <TiltyIMU.h>

TiltyIMU tilty;

void setup() {
	tilty = TiltyIMU();
	Serial.begin(115200);
	while (!Serial) {};
	Serial.println("Beginning");
	tilty.initializeIMU();
}

float ypr[3];
float altitude;

void loop() {
	//readAltitude(&altitude);
	Serial.println("Start Loop");
	
	//readAngles(ypr);
	for (int i = 0; i < 3; i++) {
		Serial.print(ypr[i]);
		Serial.print("\t\t");
	}
	Serial.println();
}