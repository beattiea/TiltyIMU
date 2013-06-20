/*!@addtogroup HiTechnic
 * @{
 * @defgroup htmc Compass Sensor
 * HiTechnic Compass Sensor
 * @{
 */
 
 /** \file HTMC_driver.h
 * \brief HiTechnic Compass Sensor driver
 *
 * HTMC_driver.h provides an API for the HiTechnic Compass Sensor.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1: 
 *        - Renamed the driver files from "HTMC" to "HTMC_driver"
 *        - Renamed the class from "HTMC" to "ClassHTMC"
 *        - Added doxygen documentation support
 *        - Added calibration support
 *        
 * Credits:
 *  - Based on Xander Soldaat's awesome ROBOTC drivers
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * \author Matthew Richardson http://mattallen37.wordpress.com/ (matthewrichardson37_at_gmail.com)
 * \date April 11 2012
 * \version 1.1
 * \example Example_HiTechnic_Compass.ino
 * \example Example_HiTechnic_Compass_Calibrate.ino 
 */

#include "HTMC_driver.h"

static byte HTMC_I2CReply[2];

ClassHTMC::ClassHTMC(byte i2c_address)
 : NXShieldI2C(i2c_address)
{
}

/**
 * Return the current absolute heading
 * @return heading in degrees (0 - 359), or -1 if an error occurred.
 */

int ClassHTMC::ReadHeading()
{
	if(!readRegisters(0x42, 2, HTMC_I2CReply))
    return -1;

	return HTMC_I2CReply[0] * 2 + HTMC_I2CReply[1];
}

/**
 * Start the calibration. The sensor should be rotated a little more than 360 along the
 * horizontal plane in no less than 20 seconds.  After the sensor has been rotated,
 * call StopCal() to set the sensor back in measurement mode and save the
 * calibration data.  This calibration data is stored in the sensor until the
 * next calibration.
 * @return true if no error occured, otherwise false
 */

bool ClassHTMC::StartCal()
{
  return writeByte(0x41, 0x43);
}

/**
 * Stop the calibration. This should be called no less than 20 seconds after
 * StartCal() and only if the sensor has been rotated more than 360 degrees
 * @return true if no error occured, otherwise false
 */

bool ClassHTMC::StopCal()
{
  if(!writeByte(0x41, 0x00)){
    return false;
  }    
  
  if(readByte(0x41) == 2){
    return false;
  }
  
  return true;
}