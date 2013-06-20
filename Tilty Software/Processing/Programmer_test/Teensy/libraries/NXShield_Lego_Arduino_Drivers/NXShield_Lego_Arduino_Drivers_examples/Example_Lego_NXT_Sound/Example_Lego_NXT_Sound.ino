/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 17 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the Lego Sound Sensor drivers of the NXShield Lego Arduino Drivers suite.
*
*  For NXTSound_driver version 1.2
*/

#include <Wire.h>
#include <NXShield.h>
#include <NXTSound_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassNXTSound sound;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);
  
  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C

  // Initialize the i2c sensors.
  sound.init( &nxshield, SH_BBS1 );
  
  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variables to store sensor values
int  soundLevel;

void loop()
{ 
  if(nxshield.getButtonState(BTN_LEFT)){
    sound.SetDB();
  }
  else if(nxshield.getButtonState(BTN_RIGHT)){
    sound.SetDBA();
  }
  
  soundLevel = sound.SoundLevel();                         // Read Gyro rotation
      
  sprintf (str, "NXT Sound: %4.d", soundLevel); // format
  Serial.println(str);                                      // send
  
  delay(50);
}
