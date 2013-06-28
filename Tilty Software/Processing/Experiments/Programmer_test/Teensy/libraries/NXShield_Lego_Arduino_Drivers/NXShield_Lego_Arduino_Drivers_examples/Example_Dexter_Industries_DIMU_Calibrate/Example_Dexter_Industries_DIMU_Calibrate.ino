/*
*  Matthew Richardson
*  matthewrichardson37<at>gmail.com
*  http://mattallen37.wordpress.com/
*  Initial date: Nov. 04 2011
*  Last updated: Apr. 11 2012
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is an example program to demonstrate the Dexter Industries dIMU drivers of the NXShield Lego Arduino Drivers suite.
*
*  For DIMU_driver version 1.1
*/

#include <Wire.h>
#include <NXShield.h>
#include <DIMU_driver.h>

//
// declare the NXShield(s) attached to your Arduino.
//
NXShield    nxshield;

//
// declare the i2c devices used on NXShield(s).
//
ClassDIMUGyro  Gyro;
ClassDIMUAccel Accel;

void setup()
{
  char str[256];

  Serial.begin(115200);  // start serial for output

  Serial.println ("Initializing the devices ...");

  //
  // Initialize the protocol for NXShield
  // It is best to use Hardware I2C (unless you want to use Ultrasonic).
  //
  nxshield.init(SH_SoftwareI2C);

  //
  // Initialize the i2c sensors.
  //
  Gyro.init(&nxshield, SH_BAS1);
  Gyro.Config(DIMU_GYRO_RANGE_250);
  
  Accel.init(&nxshield, SH_BAS1);
  Accel.Config(DIMU_ACCEL_RANGE_2G);
  
  //
  // Wait until user presses GO button to continue the program
  //
  Serial.println ("Press GO button to continue");
    nxshield.waitForButtonPress(BTN_GO);

}

void loop()
{
  char str[256];
  float Gx, Gy, Gz, Ax, Ay, Az;
  long Gxi, Gyi, Gzi, Axi, Ayi, Azi;
  while (true) { 

    if(nxshield.getButtonState(BTN_LEFT)){
      while(nxshield.getButtonState(BTN_LEFT));
      
      if(Accel.Calibrate()){
        delay(250);
        nxshield.ledSetRGB(0, 8, 0);
        delay(250);
        nxshield.ledSetRGB(0, 0, 0);
        delay(250);
        nxshield.ledSetRGB(0, 8, 0);
        delay(250);
        nxshield.ledSetRGB(0, 0, 0);       
      }
      else{
        delay(250);
        nxshield.ledSetRGB(8, 0, 0);
        delay(250);
        nxshield.ledSetRGB(0, 0, 0);
        delay(250);
        nxshield.ledSetRGB(8, 0, 0);
        delay(250);
        nxshield.ledSetRGB(0, 0, 0); 
      }
    }
    
    Gyro.ReadAxes(Gx, Gy, Gz);
    Accel.ReadAxes10Bit(Ax, Ay, Az);
    
    Gxi = Gx;      // Arduino sprintf doesn't support float, so convert to int
    Gyi = Gy;      //             ''
    Gzi = Gz;      //             ''

    Axi = Ax * 100; // Arduino sprintf doesn't support float, so multiply by 100 and convert to int
    Ayi = Ay * 100; //             ''
    Azi = Az * 100; //             ''

    sprintf (str, "dIMU Accel: X: %5ld   Y: %5ld   Z: %5ld   dIMU Gyro: X: %5ld   Y: %5ld   Z: %5ld", Axi, Ayi, Azi, Gxi, Gyi, Gzi);
    Serial.println(str);

    delay(25);
  }
}
