#include <i2c_t3.h>

char buff[6];

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
    delay(1);
}

void loop()
{
	Wire.requestFrom(0x03, 8);
	delay(5);
	if (Wire.available()) {
		/*
		long value = (Wire.read() << 24);
		value |= (Wire.read() << 16);
		value |= (Wire.read() << 8);
		value |= Wire.read();
		Serial.println(value);
		*/
		long value = 0;
		for (int i = 0; i < 4; i++) {
			char data = Wire.read();
			Serial.print("Data ");
			Serial.print(i);
			Serial.print(": ");
			Serial.println(data, HEX);
			value |= (data << ((3 - i) * 8));
		}
		Serial.print("Encoder 1: ");
		Serial.println(value);
		
		value = 0;
		for (int i = 0; i < 4; i++) {
			char data = Wire.read();
			Serial.print("Data ");
			Serial.print(i);
			Serial.print(": ");
			Serial.println(data, HEX);
			value |= (data << ((3 - i) * 8));
		}
		Serial.print("Encoder 2: ");
		Serial.println(value);
		
		/*
		for (int i = 0; i < 4; i++) {
			Serial.println(Wire.read());
		}
		*/
		Serial.println();
	}   
    delay(10);
}
