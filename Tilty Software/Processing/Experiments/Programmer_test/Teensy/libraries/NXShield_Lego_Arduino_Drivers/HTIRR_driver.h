/*
*  header file for HTIRR_driver
*  version 1.1
*/

#ifndef __HTIRR_H__
#define __HTIRR_H__

#define HTIRR_I2C_ADDR  0x02  /*!< IR Receiver I2C address */

#define HTIRR_CHANNEL_1 0     /*!< Channel 1 */
#define HTIRR_CHANNEL_2 2     /*!< Channel 2 */
#define HTIRR_CHANNEL_3 4     /*!< Channel 3 */
#define HTIRR_CHANNEL_4 6     /*!< Channel 4 */

#define HTIRR_MOTOR_1A  0     /*!< Channel 1, motor A */
#define HTIRR_MOTOR_1B  1     /*!< Channel 1, motor B */
#define HTIRR_MOTOR_2A  2     /*!< Channel 2, motor A */
#define HTIRR_MOTOR_2B  3     /*!< Channel 2, motor B */
#define HTIRR_MOTOR_3A  4     /*!< Channel 3, motor A */
#define HTIRR_MOTOR_3B  5     /*!< Channel 3, motor B */
#define HTIRR_MOTOR_4A  6     /*!< Channel 4, motor A */
#define HTIRR_MOTOR_4B  7     /*!< Channel 4, motor B */

#include "NXShieldI2C.h"

class ClassHTIRR : public NXShieldI2C
{
public:
  ClassHTIRR(byte i2c_address = HTIRR_I2C_ADDR);
  
  bool ReadChannel(byte Channel, char & a, char & b);
  bool ReadAllChannels(byte* buf);
};

#endif