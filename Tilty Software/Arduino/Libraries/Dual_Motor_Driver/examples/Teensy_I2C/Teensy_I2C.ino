#include <i2c_t3.h>
#include "DualMotorDriver.h"

char buff[6];

MotorDriver motors;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);// Works at 800 kHz too apparently
    delay(1);
}

int count = 0;

void loop()
{
	/*
	while (Wire.requestFrom(0x03, 4) != 4);
	
	union enc_union {
		uint8_t bytes[4];
		long int32;
	} enc_union;
	
	for (int i = 0; i < 4; i++) {
		enc_union.bytes[i] = Wire.read();
		//Serial.println(enc_union.bytes[i], HEX);
		Serial.println(Wire.read(), HEX);
	}
	
	Serial.println("Encoder
	Serial.println(enc_union.int32);

	Serial.println();
	delay(5);

	for (int16_t i = -255; i < 255; i++) {
		motors.setMotors(i, i);
		delay(2);
	}
	
	for (int16_t i = 255; i > -255; i--) {
		motors.setMotors(i, i);
		delay(2);
	}
	*/
	int i = 0;
	int low, high;
	while (! Serial.available() && i < 256) {
		motors.setMotors(0, i);
		i++;
		delay(50);
		high = i;
	}
	Serial.read();
	while (!Serial.available() && i > 0) {
		motors.setMotors(0, i);
		i--;
		delay(50);
		low = i;
	}
	Serial.read();
	Serial.print("High: ");
	Serial.println(high);
	Serial.print("Low: ");
	Serial.println(low);
	while (!Serial.available()) {}
	Serial.read();
}
