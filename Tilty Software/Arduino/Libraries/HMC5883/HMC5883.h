#include "Arduino.h"
#include <i2c_t3.h>

#ifndef HMC5883_h
#define HMC5883_h

#define HMC5883_ADDR 0x1E // 7 bit address of the HMC5883 used with the Wire library
#define HMC_POS_BIAS 1
#define HMC_NEG_BIAS 2

// HMC5883 register map. For details see HMC5883 datasheet
#define HMC5883_R_CONFA 0
#define HMC5883_R_CONFB 1
#define HMC5883_R_MODE 2
#define HMC5883_R_XM 3
#define HMC5883_R_XL 4


#define HMC5883_R_YM (7)  //!< Register address for YM.
#define HMC5883_R_YL (8)  //!< Register address for YL.
    #define HMC5883_R_ZM (5)  //!< Register address for ZM.
    #define HMC5883_R_ZL (6)  //!< Register address for ZL.

    #define HMC5883_X_SELF_TEST_GAUSS (+1.16)                       //!< X axis level when bias current is applied.
    #define HMC5883_Y_SELF_TEST_GAUSS (HMC5883_X_SELF_TEST_GAUSS)   //!< Y axis level when bias current is applied.
    #define HMC5883_Z_SELF_TEST_GAUSS (+1.08)                       //!< Y axis level when bias current is applied.

    #define SELF_TEST_LOW_LIMIT  (243.0/390.0)   //!< Low limit when gain is 5.
    #define SELF_TEST_HIGH_LIMIT (575.0/390.0)   //!< High limit when gain is 5.


#define HMC5883_R_STATUS 9
#define HMC5883_R_IDA 10
#define HMC5883_R_IDB 11
#define HMC5883_R_IDC 12

/**
*@class HMC5883
*/
class HMC5883
{
	public:
		HMC5883();
		bool init(bool mode);
		void setMode(unsigned char mode);
		void setDOR(unsigned char DOR);
		void setGain(unsigned char gain);
		void getValues(int *x,int *y,int *z);
		void getValues(float *x,float *y,float *z);
		void getValues(float *xyz);
		void getRaw(int *x,int *y,int *z);
		void getID(char id[3]);
	private:
		void writeRegister(unsigned char reg, unsigned char val);
		float x_scale,y_scale,z_scale,x_max,y_max,z_max;
};
#endif