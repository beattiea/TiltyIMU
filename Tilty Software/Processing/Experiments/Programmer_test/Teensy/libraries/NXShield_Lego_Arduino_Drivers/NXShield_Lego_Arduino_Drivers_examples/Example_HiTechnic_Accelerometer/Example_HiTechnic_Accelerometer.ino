/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 10 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the HiTechnic Accelerometer drivers of the NXShield Lego Arduino Drivers suite.
*
*  For HTAC_driver version 1.1
*/

#include <Wire.h>
#include <NXShield.h>
#include <HTAC_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassHTAC      HTAcc;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);
  
  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C

  // Initialize the i2c sensors.
  HTAcc.init( &nxshield, SH_BAS1 );
  
  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variables to store sensor values
int  HT_Acc_X, HT_Acc_Y, HT_Acc_Z;

void loop()
{  
  HT_Acc_X = HTAcc.ReadAxis(AXIS_X);                // Read one axis at a time
  HT_Acc_Y = HTAcc.ReadAxis(AXIS_Y);                //           ''
  HT_Acc_Z = HTAcc.ReadAxis(AXIS_Z);                //           ''

  sprintf (str, "HiTechnic Accelerometer    ReadAxis   X: %4.d   Y: %4.d   Z: %4.d", HT_Acc_X, HT_Acc_Y, HT_Acc_Z); // format
  Serial.print(str);                              // send
    
  HTAcc.ReadAxes(HT_Acc_X, HT_Acc_Y, HT_Acc_Z);     // Read all three axes at once
  
  sprintf (str, "    ReadAxes   X: %4.d   Y: %4.d   Z: %4.d", HT_Acc_X, HT_Acc_Y, HT_Acc_Z); // format
  Serial.println(str);                              // send

  delay(50);
}
