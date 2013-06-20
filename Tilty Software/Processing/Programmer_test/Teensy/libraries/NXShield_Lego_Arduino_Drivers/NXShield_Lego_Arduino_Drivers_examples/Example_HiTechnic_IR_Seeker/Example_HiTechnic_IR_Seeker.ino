/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 10 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the HiTechnic IR Seeker drivers of the NXShield Lego Arduino Drivers suite.
*
*  For HTIRS_driver version 1.1
*/

#include <Wire.h>
#include <NXShield.h>
#include <HTIRS_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassHTIRS      HTIRSeeker;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);
  
  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C

  // Initialize the i2c sensors.
  HTIRSeeker.init( &nxshield, SH_BAS1 );
  
  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variables to store sensor values
byte Direction, s1, s2, s3, s4, s5;

void loop()
{   
  Direction = HTIRSeeker.ReadDirection();                  // Read the direction
  sprintf (str, "HiTechnic IR Seeker ReadDirection: %3.d", Direction);  // format
  Serial.print(str);                                     // send
  
  Direction = HTIRSeeker.ReadStrength(s1, s2, s3, s4, s5); // Read the direction and strengths
  sprintf (str, "    ReadStrength Direction: %3.d   Strengths   S1: %3.d   S2: %3.d   S3: %3.d   S4: %3.d   S5: %3.d", Direction, s1, s2, s3, s4, s5); // format
  Serial.println(str);                                     // send
  
  delay(50);
}
