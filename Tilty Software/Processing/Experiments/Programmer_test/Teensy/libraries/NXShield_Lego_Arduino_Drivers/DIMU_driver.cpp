/*!@addtogroup Dexter_Industries
 * @{
 * @defgroup dimu DIMU
 * Dexter Industries DIMU Sensor
 * @{
 */
 
 /** \file DIMU_driver.h
 * \brief Dexter Industries DIMU Sensor driver
 *
 * DIMU_driver.h provides an API for the Dexter Industries DIMU.
 *
 * Changelog:
 * - 1.0: - Initial release (not part of the NXShield Lego Arduino Drivers suite)
 * - 1.1:
 *        - Renamed the driver files from "dIMU" to "DIMU_driver"
 *        - Renamed class "dIMUGyro" to "ClassDIMUGyro"
 *        - Added doxygen documentation support
 *        - Renamed the Gyro "Init" function to "Config"
 *        - Added accelerometer support
 *        
 * Credits:
 *  - Based on Xander Soldaat's awesome ROBOTC drivers
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * \author Matthew Richardson http://mattallen37.wordpress.com/ (matthewrichardson37_at_gmail.com)
 * \date April 11 2012
 * \version 1.1
 * \example Example_Dexter_Industries_DIMU.ino
 * \example Example_Dexter_Industries_DIMU_Calibrate.ino 
 */

#include "DIMU_driver.h"
  
/*

  The following functions are for the gyro of the dIMU

*/

ClassDIMUGyro::ClassDIMUGyro(byte i2c_address)
:NXShieldI2C(i2c_address)
{
}

/**
 * Configure the gyro
 * @param Range Range of the gyro
 * @param Filter Optionally Enable built-in Low Pass Filter to reduce spikes in data, default true
 * @return true if no error occured, otherwise false
 */

bool ClassDIMUGyro::Config(byte Range, byte Filter){
	if(!writeByte(DIMU_GYRO_CTRL_REG2, 0x00))
    return false;
	if(!writeByte(DIMU_GYRO_CTRL_REG3, 0x08))
    return false;
	if(!writeByte(DIMU_GYRO_CTRL_REG4, Range | DIMU_CTRL4_BLOCKDATA))
    return false;
	if(!writeByte(DIMU_GYRO_CTRL_REG5, Filter ? 0x02 : 0x00))
    return false;
	if(!writeByte(DIMU_GYRO_CTRL_REG1, 0x0F))
    return false;

  switch(Range) {
    case DIMU_GYRO_RANGE_250: DIMU_Gyro_divisor = 128; break;
    case DIMU_GYRO_RANGE_500: DIMU_Gyro_divisor = 64; break;
    case DIMU_GYRO_RANGE_2000: DIMU_Gyro_divisor = 16; break;
    default: return false;
  }

  return true;
}

/**
 * Read one gyro axis' data
 * @param Axis Axis to read
 * @return the axis' rotation in degrees per second
 */

float ClassDIMUGyro::ReadAxis(byte Axis){

	switch (Axis) {
    case AXIS_X: Axis = DIMU_GYRO_X_AXIS; break;
    case AXIS_Y: Axis = DIMU_GYRO_Y_AXIS; break;
    case AXIS_Z: Axis = DIMU_GYRO_Z_AXIS; break;
  }

	return (float)(readByte(Axis) + ((int)readByte(Axis+1) << 8)) / DIMU_Gyro_divisor;
}

/**
 * Read all three axes of the gyro
 * @param x x rotation in degrees per second, return by reference
 * @param y y rotation in degrees per second, return by reference
 * @param z z rotation in degrees per second, return by reference
 */

void  ClassDIMUGyro::ReadAxes(float & x, float & y, float & z){
	x = (float)(readByte(DIMU_GYRO_X_AXIS) + ((int)readByte(DIMU_GYRO_X_AXIS+1) << 8)) / DIMU_Gyro_divisor;
	y = (float)(readByte(DIMU_GYRO_Y_AXIS) + ((int)readByte(DIMU_GYRO_Y_AXIS+1) << 8)) / DIMU_Gyro_divisor;
	z = (float)(readByte(DIMU_GYRO_Z_AXIS) + ((int)readByte(DIMU_GYRO_Z_AXIS+1) << 8)) / DIMU_Gyro_divisor;
}

/*

  The following functions are for the accelerometer of the dIMU

*/


// Make these variables local to the accel functions, with only one instance each.
static byte tBuf[6];     // byte array to use as I2C buffer.
static int ureading;      // Variable to read the RAW data into.
static float sreading;    // Variable to hold the signed value, and also get scaled for the G range.

ClassDIMUAccel::ClassDIMUAccel(byte i2c_address)
:NXShieldI2C(i2c_address)
{
}

/**
 * Configure the Accel
 * @param Range at which to operate the Accelerometer, can be 2, 4 or 8G
 * @return true if no error occured, false if it did
 */

bool ClassDIMUAccel::Config(byte Range) {
  if(!writeByte(0x16, (Range | DIMU_ACCEL_MODE_MEAS))){
    return false;
  }

  switch(Range) {
    case DIMU_ACCEL_RANGE_2G: DIMU_Accel_divisor = 64.0; break;
    case DIMU_ACCEL_RANGE_4G: DIMU_Accel_divisor = 32.0; break;
    case DIMU_ACCEL_RANGE_8G: DIMU_Accel_divisor = 16.0; break;
    return false;
  }

  return true;
}

/**
 * Read one accel axis' data in 8 bit resolution
 * @param Axis Axis to read
 * @return the axis' G force
 */

float ClassDIMUAccel::ReadAxis8Bit(byte Axis) {

	switch (Axis) {
    case AXIS_X: Axis = DIMU_ACCEL_X_AXIS_8; break;
    case AXIS_Y: Axis = DIMU_ACCEL_Y_AXIS_8; break;
    case AXIS_Z: Axis = DIMU_ACCEL_Z_AXIS_8; break;
  }

	ureading = readByte(Axis);
  sreading = (ureading > 128) ? ureading - 256 : ureading;
  return sreading / DIMU_Accel_divisor;  
}

/**
 * Read all three axes of the accel with 8 bit resolution
 * @param x x axis G force
 * @param y y axis G force
 * @param z z axis G force
 * @return true if no error occured, otherwise false
 */

bool ClassDIMUAccel::ReadAxes8Bit(float & x, float & y, float & z){

  if(!readRegisters(0x06, 3, tBuf))
    return false;
  
  ureading = tBuf[0];
  sreading = (ureading > 128) ? ureading - 256 : ureading;
  x = sreading / DIMU_Accel_divisor;
 
  ureading = tBuf[1];
  sreading = (ureading > 128) ? ureading - 256 : ureading;
  y = sreading / DIMU_Accel_divisor;
  
  ureading = tBuf[2];
  sreading = (ureading > 128) ? ureading - 256 : ureading;
  z = sreading / DIMU_Accel_divisor;  

  return true;
} 

/**
 * Read one accel axis' data in 10 bit resolution. G force range does not have an effect.
 * @param Axis Axis to read
 * @return the axis' G force
 */

float ClassDIMUAccel::ReadAxis10Bit(byte Axis) {

	switch (Axis) {
    case AXIS_X: Axis = DIMU_ACCEL_X_AXIS; break;
    case AXIS_Y: Axis = DIMU_ACCEL_Y_AXIS; break;
    case AXIS_Z: Axis = DIMU_ACCEL_Z_AXIS; break;
  }                                                              

	ureading = readInteger(Axis) & 0x3FF;
  sreading = (ureading > 511) ? ureading - 1024 : ureading;
  
	return sreading / 64;
} 

/**
 * Read all three axes of the accel with 10 bit resolution. G force range does not have an effect.
 * @param x x axis G force
 * @param y y axis G force
 * @param z z axis G force
 * @return true if no error occured, otherwise false
 */

bool ClassDIMUAccel::ReadAxes10Bit(float & x, float & y, float & z){

  if(!readRegisters(DIMU_ACCEL_ALL_AXES, 6, tBuf))
    return false;
  
  ureading = (tBuf[0] + (tBuf[1]<<8)) & 0x3FF;
  sreading = (ureading > 511) ? ureading - 1024 : ureading;
  x = sreading / 64;
 
  ureading = (tBuf[2] + (tBuf[3]<<8)) & 0x3FF;
  sreading = (ureading > 511) ? ureading - 1024 : ureading;
  y = sreading / 64;

  ureading = (tBuf[4] + (tBuf[5]<<8)) & 0x3FF;
  sreading = (ureading > 511) ? ureading - 1024 : ureading;
  z = sreading / 64;

  return true;  
}

/**
 * Calibrate the Accelerometer. The sensor must be stationary and it assumes the specified axis is inline with gravity.
 * @param Axis Axis inline with gravity, default AXIS_Z
 * @return true if it calibrated successfully, otherwise false
 */

bool ClassDIMUAccel::Calibrate(byte Axis){
  if(!WriteCalibration(0, 0, 0))    // Clear all of the calibration registers.
    return false;

  int x_offset;
  int y_offset;
  int z_offset;

  if(!readRegisters(DIMU_ACCEL_ALL_AXES, 6, tBuf))
    return false;
    
  x_offset = (tBuf[0] + (tBuf[1]<<8)) & 0x3FF;  // Convert the returned array into floating point G values
  y_offset = (tBuf[2] + (tBuf[3]<<8)) & 0x3FF;  //                ''
  z_offset = (tBuf[4] + (tBuf[5]<<8)) & 0x3FF;  //                ''
  if(x_offset > 511)x_offset -= 1023;      // Convert into a signed value
  if(y_offset > 511)y_offset -= 1023;      //                ''
  if(z_offset > 511)z_offset -= 1023;      //                ''

  // We will calibrate depending on the axis that's inline with the gravity field.
  // Positive 1G is 64 decimal, or 0x40 Hex, so we need to subtract that from the proper axis.
  switch(Axis){

    case AXIS_X:
      x_offset += ((x_offset>=0)?-0x40:0x40);   // Subtract out the 1-g that the x-axis is experiencing.
    break;
 
    case AXIS_Y:
      y_offset += ((y_offset>=0)?-0x40:0x40);   // Subtract out the 1-g that the y-axis is experiencing.    
    break;

    case AXIS_Z:
      z_offset += ((z_offset>=0)?-0x40:0x40);   // Subtract out the 1-g that the z-axis is experiencing.
    break;
  }
  
  x_offset *= (-2);
  y_offset *= (-2);
  z_offset *= (-2);

  if(!WriteCalibration(x_offset, y_offset, z_offset))
    return false;
  
  return true;
}

bool ClassDIMUAccel::WriteCalibration(int x_offset, int y_offset, int z_offset){
  tBuf[0] = x_offset;         // The offset value to write for calibration.
  tBuf[1] = x_offset>>8;      //                 ''
  tBuf[2] = y_offset;         //                 ''
  tBuf[3] = y_offset>>8;      //                 ''
  tBuf[4] = z_offset;         //                 ''
  tBuf[5] = z_offset>>8;      //                 ''
  
  return writeRegisters(0x10, 6, tBuf);
}