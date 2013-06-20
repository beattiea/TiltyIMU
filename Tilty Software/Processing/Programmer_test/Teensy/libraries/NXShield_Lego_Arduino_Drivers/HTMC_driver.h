/*
*  header file for HTMC_driver
*  version 1.1
*/

#ifndef __HTMC_H__
#define __HTMC_H__

#define HTMC_I2C_ADDR      0x02  /*!< Compass I2C address */

#include "NXShieldI2C.h"

class ClassHTMC : public NXShieldI2C
{
public:

  ClassHTMC(byte i2c_address = HTMC_I2C_ADDR);
  
  int ReadHeading();
  bool StartCal();
  bool StopCal();
};

#endif