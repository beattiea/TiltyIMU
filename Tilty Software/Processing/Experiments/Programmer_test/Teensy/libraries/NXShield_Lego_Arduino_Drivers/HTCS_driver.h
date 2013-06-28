/*
*  header file for HTCS_driver
*  version 1.1
*/

#ifndef __HTCS_H__
#define __HTCS_H__

#define HTCS_I2C_ADDR  0x02  /*!< Color Sensor I2C address */

#include "NXShieldI2C.h"

class ClassHTCS : public NXShieldI2C
{
public:

  ClassHTCS(byte i2c_address = HTCS_I2C_ADDR);
  
  int ReadColor();

  int ReadRGB(byte & r, byte & g, byte & b);
};

#endif