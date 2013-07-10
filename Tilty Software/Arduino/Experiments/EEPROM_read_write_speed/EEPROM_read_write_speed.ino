/* 
*  Use the I2C bus with EEPROM 24LC64 
*  Sketch:    eeprom.pde
*  
*  Author: hkhijhe
*  Date: 01/10/2010
* 
*   
*/

#include <Wire.h> //I2C library

#define device_address 0x50

void i2c_eeprom_write_byte( int adress, unsigned int eeaddress, byte data ) {
  int rdata = data;
  Wire.beginTransmission(adress);
  Wire.send((int)(eeaddress >> 8)); // MSB
  Wire.send((int)(eeaddress & 0xFF)); // LSB
  Wire.send(rdata);
  Wire.endTransmission();
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
void i2c_eeprom_write_page( int adress, unsigned int eeaddresspage, byte* data, byte length ) {
  Wire.beginTransmission(adress);
  //Wire.send((int)(eeaddresspage >> 8)); // MSB
  Wire.send((int)eeaddresspage); // LSB
  byte c;
  for ( c = 0; c < length; c++)
    Wire.send(data[c]);
  Wire.endTransmission();
}

byte i2c_eeprom_read_byte( int adress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(adress);
  //Wire.send((int)(eeaddress >> 8)); // MSB
  Wire.send((int)(eeaddress)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(adress,1);
  if (Wire.available()) rdata = Wire.receive();
  return rdata;
}

// maybe let's not read more than 30 or 32 bytes at a time!
void i2c_eeprom_read_buffer( int adress, unsigned int eeaddress, byte *buffer, int length ) {
  Wire.beginTransmission(adress);
  Wire.send((int)(eeaddress >> 8)); // MSB
  Wire.send((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(adress,length);
  int c = 0;
  for ( c = 0; c < length; c++ )
    if (Wire.available()) buffer[c] = Wire.receive();
}



long start;

void setup() 
{ 
  Wire.begin(); // initialise the connection
  /*
  #if defined(__AVR__) // only valid on AVR, not on 32bit platforms (eg: Arduino 2, Teensy 3.0)
    TWBR = ((F_CPU / 400000L) - 16) / 2; // see twi_init in Wire/utility/twi.c
  #elif defined(__arm__)
    #if defined(CORE_TEENSY) && F_BUS == 48000000
      I2C0_F = 0x0D;  // Teensy 3.0 at 48 or 96 MHz
      I2C0_FLT = 4;
    #elif defined(CORE_TEENSY) && F_BUS == 24000000
      I2C0_F = 0x45;  // Teensy 3.0 at 24 MHz
      I2C0_FLT = 2;
    #endif
  #endif
  */
  
  Serial.begin(460800);
  
  pinMode(13, OUTPUT);
  
  while (!Serial) {}
  digitalWrite(13, HIGH);
  /*
  Serial.println("Starting write...");
  
  
  //i2c_eeprom_write_page(device_address, 0, (byte *)data, sizeof(data)); // write to EEPROM
  long start = millis();
  for (int i = 0; i < 128; i+= 8) {
    i2c_eeprom_write_page(device_address, i, (byte *)d, sizeof(d));
    Serial.print("Writing page: ");
    Serial.println(i / 8);
    delay(5);
  }

  Serial.print("Memory written in ");
  Serial.print(millis() - start);
  Serial.println(" ms");
  */
  while (!Serial.available()) {}
  start = millis();
}

int addr, fails;
byte dat, b;
char d[8] = {5, 15, 27, 53, 71, 163, 127, 221};

void loop() {
  if (Serial.available() == 2) {
    addr = Serial.read();
    dat = Serial.read();
    
    i2c_eeprom_write_byte(device_address, addr, dat);
    
    if (addr == 127) {
      long save = millis() - start;
      
      start = millis();
      
      for (int i = 0; i < 128; i++) {
        //Serial.print("Address: ");
        //Serial.write(i);
        //Serial.print(" = ");
        b = i2c_eeprom_read_byte(device_address, i); //access an address from the memory
        if (d[i%8] != b) {
          Serial.print("Failed address: ");
          Serial.print(i);
          Serial.print("\texpected: ");
          Serial.print(int(d[i%8]));
          Serial.print("   \tfound: ");
          Serial.println(b);
          fails++;
        }
        //Serial.write(b); //print content to serial port
      }
      
      long load = millis() - start;
      
      Serial.print("Save Time: ");
      Serial.print(save);
      Serial.println(" ms");
      Serial.print("Load Time: ");
      Serial.print(load);
      Serial.println(" ms");
      Serial.print("Fails: ");
      Serial.println(fails);
      
      addr++;
      while (!Serial.available()) {
        fails = 0;
        start = millis();
      }
    }
  }
  delay(5);
}
/*
void loop() 
{
  byte b = 0;// = i2c_eeprom_read_byte(device_address, 0); // access the first address from the memory

  for (int i = 0; i < 128; i++) 
  {
    Serial.print("Address: ");
    Serial.print(i);
    Serial.print(" = ");
    b = i2c_eeprom_read_byte(device_address, i); //access an address from the memory
    Serial.println(b); //print content to serial port
  }
  Serial.println(" ");
  while (true) {}

}
*/
