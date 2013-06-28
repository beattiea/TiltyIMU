/*!@addtogroup HiTechnic
 * @{
 * @defgroup htirr IR Receiver Sensor
 * HiTechnic IR Receiver Sensor
 * @{
 */

/** \file HTIRR_driver.h
 * \brief HiTechnic IR Receiver driver
 *
 * HTIRR_driver.h provides an API for the HiTechnic IR Receiver.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1: 
 *        - Renamed the driver files from "HTIRR" to "HTIRR_driver"
 *        - Renamed the class from "HTIRR" to "ClassHTIRR"
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
 * \example Example_HiTechnic_IR_Receiver.ino
 */

#include "HTIRR_driver.h"

static byte HTIRR_I2CReply[2];

ClassHTIRR::ClassHTIRR(byte i2c_address)
 : NXShieldI2C(i2c_address)
{
}

/**
 * Get the speeds of the motors for a given channel.
 * @param Channel The channel to read (HTIRR_1 to HTIRR_4)
 * @param A The speed for Motor A (-100 to +100, -128 = brake) returned by reference
 * @param B The speed for Motor B (-100 to +100, -128 = brake) returned by reference
 * @return true if no error occured, otherwise false
 */

bool ClassHTIRR::ReadChannel(byte Channel, char & A, char & B)
{
	if(!readRegisters(0x42 + Channel, 2, HTIRR_I2CReply))
    return false;

  A = HTIRR_I2CReply[0];
  B = HTIRR_I2CReply[1];

	return true;  
}

/**
 * Get the speeds of the motors for all channels.
 * @param MotorSpeeds The speeds for all the motors (-100 to +100, -128 = brake) returned by reference as an unsigned byte array
 * @return true if no error occured, otherwise false
 */

bool ClassHTIRR::ReadAllChannels(byte* MotorSpeeds)
{
	if(!readRegisters(0x42, 8, MotorSpeeds))
    return false;

  return true;
}