/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 10 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the HiTechnic Color Sensor drivers of the NXShield Lego Arduino Drivers suite.
*
*  For HTCS_driver version 1.1
*/

#include <Wire.h>
#include <NXShield.h>
#include <HTCS_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassHTCS      HTColor;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);

  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C  

  // Initialize the i2c sensors.
  HTColor.init( &nxshield, SH_BAS1 );

  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variables to store sensor values
byte  Color, R, G, B;

void loop()
{  
  Color = HTColor.ReadColor();                                   //Read the color
  sprintf (str, "HiTechnic Color Sensor    ReadColor: %3.d", Color);  // format
  Serial.print(str);                                           // send
  
  Color = HTColor.ReadRGB(R, G, B);                              //Read the color and the RGB values
  sprintf (str, "    ReadRGB Color: %3.d   R: %3.d   G: %3.d   B: %3.d", Color, R, G, B); // format
  Serial.println(str);                                           // send
  
  delay(50);
}
