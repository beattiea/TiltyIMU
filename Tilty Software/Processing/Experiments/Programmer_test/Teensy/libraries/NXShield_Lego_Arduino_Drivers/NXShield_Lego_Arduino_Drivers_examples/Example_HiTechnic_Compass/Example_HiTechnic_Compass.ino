/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 10 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the HiTechnic Compass drivers of the NXShield Lego Arduino Drivers suite.
*
*  For HTMC_driver version 1.1
*/

#include <Wire.h>
#include <NXShield.h>
#include <HTMC_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassHTMC      HTCmps;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);
  
  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C

  // Initialize the i2c sensors.
  HTCmps.init( &nxshield, SH_BAS1 );
  
  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variable to store sensor value
int  Heading;

// Loop forever, outputting the current heading.
void loop()
{ 
  Heading = HTCmps.ReadHeading();                             // Read heading
  sprintf (str, "HiTechnic Compass Heading: %3.d", Heading);  // format
  Serial.println(str);                                        // send to terminal
  
  delay(50);
} 
