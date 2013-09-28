#include <i2c_t3.h>

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
    Wire.beginTransmission(0x02);
    Wire.write(random(0, 255));
    Wire.endTransmission();
    
    //delayMicroseconds(0);
    
    Wire.requestFrom(0x02, 6);
    
    if (Wire.available() >= 6) {
      //Serial.print("Read data: ");
      //Serial.println(char(Wire.read() + 48));
      for (int i = 0; i < 6; i++) {
        Serial.print("Read Data: ");
        Serial.println(Wire.read());
      }
      Serial.println();
    }
    
    delay(20);
}
