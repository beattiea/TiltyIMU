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
	/*//Reads encoder values from both motors
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
	*/

	
	Wire.beginTransmission(0x03);
	Wire.write(0xD0);
	Wire.write(127);
	Wire.endTransmission();
	Serial.println("New Cycle...");
	
	delay(5);
}
