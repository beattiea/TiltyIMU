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
    
    Gyro.ReadAxes(Gx, Gy, Gz);
    Accel.ReadAxes10Bit(Ax, Ay, Az);
    
    Gxi = Gx;
    Gyi = Gy;
    Gzi = Gz;

    Axi = Ax * 100;
    Ayi = Ay * 100;
    Azi = Az * 100;

    sprintf (str, "dIMU Accel: X: %5ld   Y: %5ld   Z: %5ld   dIMU Gyro: X: %5ld   Y: %5ld   Z: %5ld", Axi, Ayi, Azi, Gxi, Gyi, Gzi);
    Serial.println(str);
    

    Gxi = Gyro.ReadAxis(AXIS_X);
    Gyi = Gyro.ReadAxis(AXIS_Y);
    Gzi = Gyro.ReadAxis(AXIS_Z);

    Axi = Accel.ReadAxis10Bit(AXIS_X) * 100;
    Ayi = Accel.ReadAxis10Bit(AXIS_Y) * 100;
    Azi = Accel.ReadAxis10Bit(AXIS_Z) * 100;

    sprintf (str, "dIMU Accel: X: %5ld   Y: %5ld   Z: %5ld   dIMU Gyro: X: %5ld   Y: %5ld   Z: %5ld", Axi, Ayi, Azi, Gxi, Gyi, Gzi);
    Serial.println(str);    
    

    Accel.ReadAxes8Bit(Ax, Ay, Az);

    Axi = Ax * 100;
    Ayi = Ay * 100;
    Azi = Az * 100;

    sprintf (str, "dIMU Accel: X: %5ld   Y: %5ld   Z: %5ld", Axi, Ayi, Azi);
    Serial.println(str);
    
    
    Axi = Accel.ReadAxis8Bit(AXIS_X) * 100;
    Ayi = Accel.ReadAxis8Bit(AXIS_Y) * 100;
    Azi = Accel.ReadAxis8Bit(AXIS_Z) * 100;    

    sprintf (str, "dIMU Accel: X: %5ld   Y: %5ld   Z: %5ld", Axi, Ayi, Azi);
    Serial.println(str);
    

    Serial.println("");    
    
    delay(250);
  }
}
