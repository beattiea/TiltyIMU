/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 17 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the HiTechnic Gyro drivers of the NXShield Lego Arduino Drivers suite.
*
*  For HTGYRO_driver version 1.2
*/

#include <Wire.h>
#include <NXShield.h>
#include <HTGYRO_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassHTGYRO HTGyro;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);
  
  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C

  // Initialize the i2c sensors.
  HTGyro.init( &nxshield, SH_BAS1 );
  
  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variables to store sensor values
int  Rotation;

void loop()
{ 
  if(nxshield.getButtonState(BTN_LEFT)){                      // If the left button is pressed
    while(nxshield.getButtonState(BTN_LEFT));
    HTGyro.Calibrate(1, 20);                    // Calibrate the Gyro. There must be 20 readings without more than 1 DPS change between.
    for(byte i = 0; i < 4; i++){
      delay(250);
      nxshield.ledSetRGB(0, 8, 0);   // ...Flash the LED green
      delay(250);
      nxshield.ledSetRGB(0, 0, 0);
    }
  }
  
  Rotation = HTGyro.ReadRotation();                         // Read Gyro rotation
      
  sprintf (str, "HiTechnic Gyro Rotation: %4.d", Rotation); // format
  Serial.println(str);                                      // send
  
  delay(50);
}
