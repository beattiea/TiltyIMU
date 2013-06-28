/*! @addtogroup HiTechnic
 * @{
 * @defgroup htgyro Gyroscopic Sensor
 * HiTechnic Gyroscopic Sensor
 * @{
 */

/** \file HTGYRO_driver.h
 * \brief HiTechnic Gyroscopic Sensor driver
 *
 * HTGYRO_driver.h provides an API for the HiTechnic Gyroscopic Sensor.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1: 
 *        - Renamed the driver files from "HTGY" to "HTGYRO_driver"
 *        - Renamed the class from "HTGY" to "ClassHTGYRO"
 *        - Added doxygen documentation support
 *        - Added calibration support
 * - 1.2:
 *        - Added function init, so that it sets the sensor type to analog
 *        
 * Credits:
 *  - Based on Xander Soldaat's awesome ROBOTC drivers
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * \author Matthew Richardson http://mattallen37.wordpress.com/ (matthewrichardson37_at_gmail.com)
 * \date April 17 2012
 * \version 1.2
 * \example Example_HiTechnic_Gyro.ino
 */

#include "HTGYRO_driver.h"

/**
 * Initialize the HiTechnic Gyro on a certain port
 * @param Shield The NXShield instance
 * @param Port The sensor port it's connected to
 * @return true if no error occured, otherwise false
 */
 
bool ClassHTGYRO::init(NXShield * shield, SH_BankPort bp)
{
	NXShieldAGS::init(shield, bp);
  return setType(SH_Type_ANALOG);
}

/**
 * Read the value of the gyro in Degrees Per Second
 * @return Degrees Per Second of Rotation
 */
  
int ClassHTGYRO::ReadRotation()
{
  return readRaw() - _offset;
}

static float CalReadings;
static int ThisRaading;
static int FirstReading;

/**
 * Create an offset to subtract from the gyro readings
 * @param NoiseLimit Optionally require the readings to not vary more than n DPS
 * @param Samples Optionally set the number of samples to take
 * @return calibration offset
 */

int ClassHTGYRO::Calibrate(byte NoiseLimit, int Samples){
__ClassHTGYRO__Calibrate__Restart__:
  CalReadings = 0;
  FirstReading = readRaw();
  delay(25);
  for(byte i = 0; i < Samples; i ++){
    ThisRaading = readRaw();
    if(NoiseLimit && (ThisRaading > FirstReading + NoiseLimit || ThisRaading < FirstReading - NoiseLimit)){
      goto __ClassHTGYRO__Calibrate__Restart__;
    }
    CalReadings += ThisRaading; 
    delay(25);
  }
  _offset = CalReadings / Samples;
  return _offset;
}







