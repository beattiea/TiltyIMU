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
	Wire.beginTransmission(0x02);
	Wire.write(0b01011000);
	Wire.write(0);
	//Wire.write(buff[0]);
    Wire.endTransmission();
	delay(1500);
	*/

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
