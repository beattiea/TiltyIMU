#include <i2c_t3.h>

void setup() {
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
	while (!Serial) {}
}

void loop() {
	Serial.println("I2C Devices on 5v Line:");
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}	
	Serial.println();
	
	Serial.println("I2C Devices on 3v3 line:");
	Wire.pinConfigure(I2C_PINS_18_19, I2C_PULLUP_EXT);
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}
	
	while (!Serial.available()) {}
	
	Wire.pinConfigure(I2C_PINS_16_17, I2C_PULLUP_EXT);
	Serial.read();
	Serial.println();
}