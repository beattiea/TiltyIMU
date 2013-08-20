#include <TiltyIMU.h>

#include <i2c_t3.h>
#include <FastServo.h> // Uncomment this line to use Fast Servo library
//#include <Servo.h> // Uncomment this line to use standard Servo library

#include <I2Cdev.h>
#define INCLUDE_DMP

TiltyIMU tilty;

float ypr[3];
float alt;

void setup() {
	while (!Serial) {}
	tilty.init();
}

void loop() {
	tilty.updateIMU();
	tilty.readNormalAccelerations(ypr);
	
	Serial.print(ypr[0]);
	Serial.print("\t\t");
	Serial.print(ypr[1]);
	Serial.print("\t\t");
	Serial.println(ypr[2]);
	
	//Serial.println(tilty.readAltitude(&alt));
}