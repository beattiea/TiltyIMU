/*
*  header file for HTGYRO_driver
*  version 1.2
*/

#ifndef __HTGYRO_H__
#define __HTGYRO_H__

#include "NXShieldAGS.h"

class ClassHTGYRO : public NXShieldAGS
{
public:
  bool init(NXShield * shield, SH_BankPort bp);

	int ReadRotation();
  
  int Calibrate(byte NoiseLimit = false, int samples = 10);

private:
  float _offset;
};

#endif