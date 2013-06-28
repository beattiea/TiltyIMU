/*
*  header file for DIMU_driver
*  version 1.1
*/

#ifndef __DIMU_H__
#define __DIMU_H__


#define AXIS_X 0  /*!< X Axis for dIMU */
#define AXIS_Y 1  /*!< Y Axis for dIMU */
#define AXIS_Z 2  /*!< Z Axis for dIMU */


#define DIMU_GYRO_I2C_ADDR      0xD2  /*!< Gyro I2C address */

#define DIMU_GYRO_RANGE_250     0x00  /*!< 250 dps range */
#define DIMU_GYRO_RANGE_500     0x10  /*!< 500 dps range */
#define DIMU_GYRO_RANGE_2000    0x30  /*!< 2000 dps range */

#define DIMU_CTRL4_BLOCKDATA    0x80

#define DIMU_GYRO_CTRL_REG1     0x20  // CTRL_REG1 for Gyro
#define DIMU_GYRO_CTRL_REG2     0x21  // CTRL_REG2 for Gyro
#define DIMU_GYRO_CTRL_REG3     0x22  // CTRL_REG3 for Gyro
#define DIMU_GYRO_CTRL_REG4     0x23  // CTRL_REG4 for Gyro
#define DIMU_GYRO_CTRL_REG5     0x24  // CTRL_REG5 for Gyro

#define DIMU_GYRO_ALL_AXES      0x28  // All Axes for Gyro
#define DIMU_GYRO_X_AXIS        0x2A  // X Axis for Gyro
#define DIMU_GYRO_Y_AXIS        0x28  // Y Axis for Gyro
#define DIMU_GYRO_Z_AXIS        0x2C  // Z Axis for Gyro


#define DIMU_ACCEL_I2C_ADDR     0x3A  /*!< Accelerometer I2C address */

#define DIMU_ACCEL_RANGE_2G     0x04  /*!< Accelerometer 2G range */
#define DIMU_ACCEL_RANGE_4G     0x08  /*!< Accelerometer 4G range */
#define DIMU_ACCEL_RANGE_8G     0x00  /*!< Accelerometer 8G range */

#define DIMU_ACCEL_MODE_STBY    0x00  // Accelerometer standby mode
#define DIMU_ACCEL_MODE_MEAS    0x01  // Accelerometer measurement mode
#define DIMU_ACCEL_MODE_LVLD    0x02  // Accelerometer level detect mode
#define DIMU_ACCEL_MODE_PLSE    0x03  // Accelerometer pulse detect mode

#define DIMU_ACCEL_ALL_AXES     0x00  // All Axes for Accel
#define DIMU_ACCEL_X_AXIS       0x00  // X Axis for Accel
#define DIMU_ACCEL_Y_AXIS       0x02  // Y Axis for Accel
#define DIMU_ACCEL_Z_AXIS       0x04  // Z Axis for Accel

#define DIMU_ACCEL_X_AXIS_8     0x06  // 8 bit X Axis for Accel
#define DIMU_ACCEL_Y_AXIS_8     0x07  // 8 bit Y Axis for Accel
#define DIMU_ACCEL_Z_AXIS_8     0x08  // 8 bit Z Axis for Accel

#include "NXShieldI2C.h"


//  dIMU gyro class
class ClassDIMUGyro : public NXShieldI2C
{
public:
  ClassDIMUGyro(byte i2c_address = DIMU_GYRO_I2C_ADDR);
  
  bool  Config(byte range, byte filter = true);
  
  float ReadAxis(byte axis_reg);
  void  ReadAxes(float & x, float & y, float & z);

private:
  byte DIMU_Gyro_divisor;  
};


//  dIMU accelerometer class
class ClassDIMUAccel : public NXShieldI2C
{
public:
  ClassDIMUAccel(byte i2c_address = DIMU_ACCEL_I2C_ADDR);
  
  bool  Config(byte range);
  
  float ReadAxis8Bit(byte axis_reg);
  bool  ReadAxes8Bit(float & x, float & y, float & z);
  
  float ReadAxis10Bit(byte axis_reg);
  bool  ReadAxes10Bit(float & x, float & y, float & z);
  
  bool  Calibrate(byte VerticalAxis = AXIS_Z);

private:
  bool  WriteCalibration(int x_offset, int y_offset, int z_offset);
  
  byte DIMU_Accel_divisor;  
};
  
#endif