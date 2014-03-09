#include "DualMotorDriver.h"
#include "i2c_t3.h"

void setup() {
	Wire.begin(I2C_MASTER, 0, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
	pinMode(13, OUTPUT);
	
	while (!Serial);
	
	//setup1819();
}

void loop() {
	long start = micros();
	Serial.println("Motor 1:");
	MotorDriver.readMotor(1);
	
	Serial.println();
	
	Serial.print("Time: ");
	Serial.println(micros() - start);
	Serial.println("\n");
	
	while (!Serial.available());
	Serial.read();
	
	MotorDriver.setMotorSpeed(1, random(0, 255));
}