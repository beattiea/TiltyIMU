/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 10 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the HiTechnic IR Receiver drivers of the NXShield Lego Arduino Drivers suite.
*
*  For HTIRR_driver version 1.1
*/

#include <Wire.h>
#include <NXShield.h>
#include <HTIRR_driver.h>

// declare the NXShield(s) attached to your Arduino.
NXShield    nxshield;

// declare the i2c devices used on NXShield(s).
ClassHTIRR       HTIRRec;

// String to store messages to send to terminal
char str[256];

void setup()
{
  Serial.begin(115200);
  
  // Initialize the protocol for NXShield
//  nxshield.init( SH_SoftwareI2C );   //Software or
  nxshield.init( SH_HardwareI2C );   //Hardware I2C

  // Initialize the i2c sensors.
  HTIRRec.init( &nxshield, SH_BAS1 );
  
  // Wait until user presses GO button to continue the program
  Serial.println ("Press GO button to continue");
	nxshield.waitForButtonPress(BTN_GO);
}

// variables to store sensor values
byte pfData[8];
char  HT_IR_VAL_0, HT_IR_VAL_1, HT_IR_VAL_2, HT_IR_VAL_3, HT_IR_VAL_4, HT_IR_VAL_5, HT_IR_VAL_6, HT_IR_VAL_7;

void loop()
{ 
 
  HTIRRec.ReadChannel(HTIRR_CHANNEL_1, HT_IR_VAL_0, HT_IR_VAL_1);  // Read one channel at a time
  HTIRRec.ReadChannel(HTIRR_CHANNEL_2, HT_IR_VAL_2, HT_IR_VAL_3);  //          ''
  HTIRRec.ReadChannel(HTIRR_CHANNEL_3, HT_IR_VAL_4, HT_IR_VAL_5);  //          ''
  HTIRRec.ReadChannel(HTIRR_CHANNEL_4, HT_IR_VAL_6, HT_IR_VAL_7);  //          ''
  sprintf (str, "HiTechic IR Receiver    ReadChannel: %4.d %4.d %4.d %4.d %4.d %4.d %4.d %4.d", HT_IR_VAL_0, HT_IR_VAL_1, HT_IR_VAL_2, HT_IR_VAL_3, HT_IR_VAL_4, HT_IR_VAL_5, HT_IR_VAL_6, HT_IR_VAL_7); // format
  Serial.print(str);                        // send
  
  HTIRRec.ReadAllChannels(pfData);            // Read all the values, and store them in an array
  sprintf (str, "   ReadAllChannels: %4.d %4.d %4.d %4.d %4.d %4.d %4.d %4.d", (char)pfData[HTIRR_MOTOR_1A], (char)pfData[HTIRR_MOTOR_1B], (char)pfData[HTIRR_MOTOR_2A], (char)pfData[HTIRR_MOTOR_2B], (char)pfData[HTIRR_MOTOR_3A], (char)pfData[HTIRR_MOTOR_3B], (char)pfData[HTIRR_MOTOR_4A], (char)pfData[HTIRR_MOTOR_4B]); // format
  Serial.println(str);                        // send
  
  delay(50);
}
