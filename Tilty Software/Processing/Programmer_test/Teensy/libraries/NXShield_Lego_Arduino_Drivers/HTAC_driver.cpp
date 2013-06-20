/*!@addtogroup HiTechnic
 * @{
 * @defgroup htacc Acceleration Sensor
 * HiTechnic Acceleration Sensor
 * @{
 */

/** \file HTAC_driver.h
 * \brief HiTechnic Acceleration Sensor driver
 *
 * HTAC_driver.h provides an API for the HiTechnic Accelerometer.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1:
 *        - Renamed the driver files from "HTAC" to "HTAC_driver"
 *        - Renamed the class from "HTAC" to "ClassHTAC"
 *        - Added doxygen documentation support
 *        
 * Credits:
 *  - Based on Xander Soldaat's awesome ROBOTC drivers
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * \author Matthew Richardson http://mattallen37.wordpress.com/ (matthewrichardson37_at_gmail.com)
 * \date April 10 2012
 * \version 1.1
 * \example Example_HiTechnic_Accelerometer.ino
 */

#include "HTAC_driver.h"

static byte HTAC_I2CReply[6];

ClassHTAC::ClassHTAC(byte i2c_address)
 : NXShieldI2C(i2c_address)
{
}

/**
 * Read the value of an axis
 * @param axis Axis to read
 * @return the axis value
 */

int ClassHTAC::ReadAxis(byte axis)
{
	byte hb = readByte(0x42 + axis);
  byte lb = readByte(0x45 + axis);
	return hb > 127 ? (hb - 256) * 4 + lb : hb * 4 + lb;
	//return ((readByte(0x42 + Channel) << 2) + readByte(0x45 + Channel));
}

/**
 * Read the value of all the axes. Return values by reference.
 * @param x x axis
 * @param y y axis
 * @param z z axis
 * @return true if no error occured, otherwise false
 */
 
bool ClassHTAC::ReadAxes(int & x, int & y, int & z)
{
  if(!readRegisters(0x42, 6, HTAC_I2CReply))
    return false;

  // Convert 2 bytes into a signed 10 bit value.  If the 8 high bits are more than 127, make
  // it a signed value before combing it with the lower 2 bits.
  x = (HTAC_I2CReply[0] > 127) ? (HTAC_I2CReply[0] - 256) * 4 + HTAC_I2CReply[3]
                                   : HTAC_I2CReply[0] * 4 + HTAC_I2CReply[3];

  y = (HTAC_I2CReply[1] > 127) ? (HTAC_I2CReply[1] - 256) * 4 + HTAC_I2CReply[4]
                                   : HTAC_I2CReply[1] * 4 + HTAC_I2CReply[4];

  z = (HTAC_I2CReply[2] > 127) ? (HTAC_I2CReply[2] - 256) * 4 + HTAC_I2CReply[5]
                                   : HTAC_I2CReply[2] * 4 + HTAC_I2CReply[5];

  return true;
}