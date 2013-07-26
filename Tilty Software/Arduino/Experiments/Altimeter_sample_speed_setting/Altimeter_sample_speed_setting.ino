#include <i2c_t3.h>
#include <MPL3115A2.h>


MPL3115A2 altimeter;

byte def = 0b10000011;
byte frequency = 0b00001000;
byte settings = def | frequency;

void setup() {
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
  Serial.begin(115200);
  altimeter.init();
  delay(1);
  write(0x26, settings);
}

float alt = 0;
int u_altitude, m_altitude;
float l_altitude;

void loop() {
  long start = millis();
  write(0x26, settings);
  write(0x26, 0b10000001 | frequency);
  
  while (!altimeter.checkData()) {  delay(1);}
  
  u_altitude = read(0x01) << 8;//  The upper 8 bits of the altitude
  m_altitude = read(0x02);//  The middle 8 bits of the altitude
  l_altitude = float(read(0x03) >> 4) / 16.0;//  The lower 4 bits of the altitude
  int16_t _temp = u_altitude | m_altitude;
  if (_temp < 0)
  {
    alt = float(_temp) - l_altitude;
  }
  else
  {
    alt = float(_temp) + l_altitude;
  }
  
  Serial.print("Alt: ");
  Serial.print(alt);
  Serial.print("\tTime: ");
  Serial.println(millis() - start);
}

//	Reads a byte on the sensor from the given address
byte read(byte _regAddr)
{
	Wire.beginTransmission(_addr);
	Wire.write(_regAddr);
	Wire.endTransmission(I2C_NOSTOP);
	Wire.requestFrom(_addr, 1, I2C_STOP, _timeout); // Request the data...
	return Wire.read();
}



//	Writes a byte of data to the sensor at the given address
byte write(byte _regAddr, byte _value)
{
	Wire.beginTransmission(_addr);
	Wire.write(_regAddr);
	Wire.write(_value);
	return Wire.endTransmission(I2C_STOP);
}
