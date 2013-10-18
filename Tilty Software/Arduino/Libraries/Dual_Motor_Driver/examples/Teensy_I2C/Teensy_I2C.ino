#include <i2c_t3.h>

char buff[6];

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
	Serial.print("New Cycle... #");
	Serial.println(count++);
	
	/*
	Wire.beginTransmission(0x03);// Default I2C address is 0x03
	Wire.write(0x02);
	Wire.write(127);
	Wire.write(127);
	Wire.endTransmission();
	delayMicroseconds(10);
	*/
	
	Wire.beginTransmission(0x03);// Default I2C address is 0x03
	Wire.write(0x04);
	Wire.endTransmission();
	delayMicroseconds(10);

	long start = micros();
	/*
	for (int i = 0; i < 4; i++) {
		Wire.requestFrom(0x03, 1);
	}
	*/
	while (Wire.requestFrom(0x03, 4) != 4);
	
	union enc_union {
		uint8_t bytes[4];
		long int32;
	} enc_union;
	
	for (int i = 0; i < 4; i++) {
		enc_union.bytes[i] = Wire.read();
		Serial.println(enc_union.bytes[i], HEX);
		//Serial.println(Wire.read(), HEX);
	}
	Serial.print("Encoder Value: ");
	Serial.println(enc_union.int32);
	Serial.print("Time: ");
	Serial.println(micros() - start);
	
	/*
	Serial.print("Control 1: ");
	Serial.println(Wire.read());
	Serial.print("Control 2: ");
	Serial.println(Wire.read());
	Serial.print("Power 1: ");
	Serial.println(Wire.read());
	Serial.print("Power 2: ");
	Serial.println(Wire.read());
	Serial.println();
	*/
	
	/*
	if (Serial1.available()) {
		Serial.println("====Motor Driver Output====");
		while (Serial1.available()) {
			Serial.print(char(Serial1.read()));
			delay(2);
		}
		Serial.println("==End Motor Driver Output==\n");
	}
	*/
	
	Serial.println();
	delay(5);
}
