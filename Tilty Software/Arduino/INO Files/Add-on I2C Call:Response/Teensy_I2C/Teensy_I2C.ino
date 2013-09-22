#include <i2c_t3.h>

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_100);
}

void loop()
{
    while (Serial.available()) {
      Wire.beginTransmission(0x15);
      char data = Serial.read();
      Wire.write(data - 48);
      Wire.endTransmission();
      delayMicroseconds(10);
      Wire.requestFrom(0x15, 1);
      delayMicroseconds(10);
    }
    if (Wire.available()) {
      Serial.print("Read data: ");
      Serial.println(char(Wire.read() + 48));
    }
    
    delay(100);
}
