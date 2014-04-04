#include "DualMotorDriver.h"
#include "i2c_t3.h"

void setup() {
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_200);
	pinMode(13, OUTPUT);
	
	while (!Serial);
}

int old_enc=1, d_enc;
long start = 1;

void loop() {
	/*
	start = micros();
	Serial.print("Motor 1 Previous value:");
	MotorDriver.readMotor(1);
	Serial.println(MotorDriver.motor1.set_power);
	
	//MotorDriver.setMotorSpeed(1, random(0, 255));
	MotorDriver.setMotorRPM(1, 100);
	
	Serial.print("Motor 1 Current value:");
	MotorDriver.readMotor(1);
	Serial.println(MotorDriver.motor1.set_power);
	
	Serial.println();
	
	Serial.print("Time: ");
	Serial.println(micros() - start);
	Serial.println("\n");
	
	while (!Serial.available());
	Serial.read();
	*/
	if (Serial.available()) {
		short speed = Serial.parseInt();
		MotorDriver.setMotorSpeed(1, speed);
		MotorDriver.setMotorSpeed(2, speed);
		Serial.print("\n\t\t\tSet Power to: ");
		Serial.print(speed);
		Serial.println("\n");
		
		while (Serial.available()) Serial.read();
	}
	
	
	old_enc = MotorDriver.motor2.encoder_value;
	MotorDriver.readMotor(1);
	MotorDriver.readMotor(2);
	
	d_enc = MotorDriver.motor2.encoder_value - old_enc;
	float teensy_rate = (d_enc / 334.0) * 600;
	
	Serial.print("Encoder change:\t\t");
	Serial.println(d_enc);
	Serial.print("DMD Encoder Rate:\t");
	Serial.println(MotorDriver.motor2.current_rate, 5);
	Serial.print("Teensy Encoder Rate:\t");
	Serial.println(teensy_rate, 5);
	Serial.print("Difference:\t\t");
	Serial.println(teensy_rate - MotorDriver.motor2.current_rate, 5);
	Serial.println();
	
	delayMicroseconds(micros() - start < 10000 ? 10000 - (micros() - start) : 10000);
	start = micros();
}