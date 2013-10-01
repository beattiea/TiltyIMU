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
	if (Wire.available()) {
		long value = 0;
		for (int i = 0; i < 4; i++) {
			char data = Wire.read();
			value |= (data << ((3 - i) * 8));
		}
		Serial.print("Encoder 1: ");
		Serial.println(value);
		
		value = 0;
		for (int i = 0; i < 4; i++) {
			char data = Wire.read();
			value |= (data << ((3 - i) * 8));
		}
		Serial.print("Encoder 2: ");
		Serial.println(value);
		Serial.println();
	}
	
    
	Wire.requestFrom(0x02, 6);
	if (Wire.available()) {
		for (int i = 0; i < 6; i++) {
			Serial.print("Channel ");
			Serial.print(i + 1);
			Serial.print(": ");
			buff[i] = Wire.read();
			Serial.println(int(buff[i]));
		}
		Serial.println();
	}
	
	Wire.beginTransmission(0x03);
	Wire.write(buff[0]);
	Wire.write(buff[1]);
	Wire.endTransmission();
	Serial.println("New Cycle...");
	
	delay(5);
}
