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
  /*
    while (Serial.available()) {
      Wire.beginTransmission(0x15);
      char data = Serial.read();
      Wire.write(data - 48);
      Wire.endTransmission();
      delayMicroseconds(10);
      Wire.requestFrom(0x15, 1);
      delayMicroseconds(10);
    }
    */
	for (int i = 0; i < 1024; i++) {
		char byte1 = 0b01011000 | (i >> 8);
		Serial.print("Sent Byte 1: ");
		Serial.print(byte1, HEX);
		Serial.print("\t\tSent Value: ");
		int value = (((0x0003 & byte1) << 8) | (i & 0xFF));
		Serial.println(value);
		
		Wire.beginTransmission(0x02);
		Wire.write(byte1);
		Wire.write(i & 0xFF);
	    Wire.endTransmission();
		delay(1);
		
		Wire.requestFrom(0x02, 2);
		if (Wire.available()) {
			Serial.print("Value: ");
			Serial.print(Wire.read(), HEX);
			Serial.print("\t");
			Serial.println(Wire.read(), HEX);
			//int value = (((0x0003 & Wire.read()) << 8) | Wire.read()) - 512;
			//Serial.println(value, BIN);
			Serial.println();
		}
		
	}
	Wire.beginTransmission(0x02);
	Wire.write(0b01011000);
	Wire.write(0);
	//Wire.write(buff[0]);
    Wire.endTransmission();
	delay(1500);
    
    //delayMicroseconds(0);
    
    Wire.requestFrom(0x02, 6);
    
    if (Wire.available() >= 6) {
      //Serial.print("Read data: ");
      //Serial.println(char(Wire.read() + 48));
      for (int i = 0; i < 6; i++) {
        Serial.print("Read Data: ");
		buff[i] = Wire.read();
        Serial.println(int(buff[i]));
      }
      Serial.println();
    }
    
    delay(20);
}
