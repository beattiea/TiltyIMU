/*
*  header file for HTIRS_driver
*  version 1.1
*/

#ifndef __HTIRS_H__
#define __HTIRS_H__

#define HTIRS_I2C_ADDR      0x02  /*!< IR Seeker I2C address */

#include "NXShieldI2C.h"

class ClassHTIRS : public NXShieldI2C
{
public:

  ClassHTIRS(byte i2c_address = HTIRS_I2C_ADDR);
  
  int ReadDirection();

  int ReadStrength(byte & s1, byte & s2, byte & s3, byte & s4, byte & s5);
};

#endif