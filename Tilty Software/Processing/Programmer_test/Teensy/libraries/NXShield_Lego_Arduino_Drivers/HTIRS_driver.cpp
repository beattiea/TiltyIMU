/*!@addtogroup HiTechnic
 * @{
 * @defgroup htirs IR Seeker V1
 * HiTechnic IR Seeker V1
 * @{
 */

/** \file HTIRS_driver.h
 * \brief HiTechnic IR Seeker driver
 *
 * HTIRS_driver.h provides an API for the HiTechnic IR Seeker.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1: 
 *        - Renamed the driver files from "HTIRS" to "HTIRS_driver"
 *        - Renamed the class from "HTIRS" to "ClassHTIRS"
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
 * \example Example_HiTechnic_IR_Seeker.ino
 */

#include "HTIRS_driver.h"

static byte HTIRS_I2CReply[6];

ClassHTIRS::ClassHTIRS(byte i2c_address)
 : NXShieldI2C(i2c_address)
{
}

/**
 * Read the value of the DC IR Direction.
 * @return value of 0-9, the direction index of the detected IR signal, or -1 if an error occurred.
 */

int ClassHTIRS::ReadDirection()
{
	if(!readRegisters(0x42, 1, HTIRS_I2CReply))
    return -1;

	return HTIRS_I2CReply[0];
}

/**
 * Read the value of the all of the internal sensors.
 * @param S1 Sensor 1 IR Strength
 * @param S2 Sensor 2 IR Strength
 * @param S3 Sensor 3 IR Strength
 * @param S4 Sensor 4 IR Strength
 * @param S5 Sensor 5 IR Strength
 * @return value of 0-9, the direction index of the detected IR signal, or -1 if an error occurred.
 */

int ClassHTIRS::ReadStrength(byte & S1, byte & S2, byte & S3, byte & S4, byte & S5)
{
	if(!readRegisters(0x42, 6, HTIRS_I2CReply))
    return -1;

	S1 = HTIRS_I2CReply[1];
	S2 = HTIRS_I2CReply[2];
	S3 = HTIRS_I2CReply[3];
	S4 = HTIRS_I2CReply[4];
	S5 = HTIRS_I2CReply[5];

	return HTIRS_I2CReply[0];
}