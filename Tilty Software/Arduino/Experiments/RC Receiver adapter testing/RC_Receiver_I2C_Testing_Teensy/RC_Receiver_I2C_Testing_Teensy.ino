#include <i2c_t3.h>

void setup() {
	Serial.begin(115200);
	//Serial3.begin(9600);
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_100);
	delay(500);
}

void loop() {
	
        Wire.requestFrom(2, 1);
        delay(100);
        Serial.print("Read from Add-on: ");
	Serial.println(Wire.read());
	//Serial.println(Wire.endTransmission(I2C_STOP));
	/*
	Wire.requestFrom(2, 1);

	while (!Wire.available()) {
		delay(250);
		Serial.println("Waiting for data...");
	}
	
	int value = (Wire.read() << 8) | (Wire.read());
	
	Serial.print("Value: ");
	Serial.print(Wire.read());
	
	Serial.print(value);
	Serial.print("\t\t");
	Serial.print(value >> 8, HEX);
	Serial.print(", ");
	Serial.print(value & 0xFF, HEX);
	*/
	/*
	if (Serial3.available()) {
		Serial.print("Add-on Board: ");
		char data;
		while (data != '\n') {
			if (Serial3.available()) {
				data = Serial3.read();
				Serial.print(data);
			}
		}
		Serial.println();
	}*/
	
	//delay(1000);
}
