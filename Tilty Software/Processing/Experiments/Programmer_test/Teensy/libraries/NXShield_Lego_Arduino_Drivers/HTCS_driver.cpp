/*!@addtogroup HiTechnic
 * @{
 * @defgroup htcs Color Sensor V1
 * HiTechnic Color Sensor V1
 * @{
 */

/** \file HTCS_driver.h
 * \brief HiTechnic Color Sensor driver
 *
 * HTCS_driver.h provides an API for the HiTechnic Color Sensor.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1:
 *        - Renamed the driver files from "HTAC" to "HTCS_driver"
 *        - Renamed the class from "HTCS" to "ClassHTCS"
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
 * \example Example_HiTechnic_Color_Sensor.ino
 */

#include "HTCS_driver.h"

static byte HTCS_I2CReply[4];

ClassHTCS::ClassHTCS(byte i2c_address)
 : NXShieldI2C(i2c_address)
{
}

/**
 * Return the color number currently detected
 * @return color index number, or -1 if an error occured
 */

int ClassHTCS::ReadColor()
{
	if(!readRegisters(0x42, 1, HTCS_I2CReply))
    return -1;

	return HTCS_I2CReply[0];
}

/**
 * Get the detection levels for the three color components. Return values by reference.
 * @param Red the red value
 * @param Green the green value
 * @param Blue the blue value
 * @return color index number, or -1 if an error occured
 */

int ClassHTCS::ReadRGB(byte & Red, byte & Green, byte & Blue)
{
	if(!readRegisters(0x42, 4, HTCS_I2CReply))
    return -1;
    
	Red   = HTCS_I2CReply[1];
	Green = HTCS_I2CReply[2];
	Blue  = HTCS_I2CReply[3];

	return HTCS_I2CReply[0];
}