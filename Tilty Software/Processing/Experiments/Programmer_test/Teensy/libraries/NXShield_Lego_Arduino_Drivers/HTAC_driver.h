/*
*  header file for HTAC_driver
*  version 1.1
*/

#ifndef __HTAC_H__
#define __HTAC_H__

#define HTAC_I2C_ADDR  0x02  /*!< Accelerometer I2C address */

#define AXIS_X 0             /*!< X Axis for accel sensor */
#define AXIS_Y 1             /*!< Y Axis for accel sensor */
#define AXIS_Z 2             /*!< Z Axis for accel sensor */

#include "NXShieldI2C.h"

class ClassHTAC : public NXShieldI2C
{
public:

  ClassHTAC(byte i2c_address = HTAC_I2C_ADDR);
  
  int ReadAxis(byte axis);
  bool ReadAxes(int & x, int & y, int & z);
};

#endif