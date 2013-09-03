/**
* @author Tyler Pawlaczyk (@embedeek)
* @file HMC5883.cpp
* 
*/

#include "Tilty_HMC5883.h"

const int counts_per_milligauss[8]={  
	1370,
	1090,
	820,
	660,
	440,
	390,
	330,
	230
};

/**
* 
*/
HMC5883::HMC5883()
{
	x_scale = (float) 1.0;
	y_scale = (float) 1.0;
	z_scale = (float) 1.0;
}

HMC5883::~HMC5883()
{
	//	Do nothing
}

/**
* @param[in] mode Set mode to 0 if true. Otherwise you must set the mode using setMode().
*/ 
bool HMC5883::init()
{
	char deviceID[3];
	getID(deviceID);
	
	if (deviceID[0] == 'H' && deviceID[1] == '4' && deviceID[2] == '3')
	{
		setMode(0);
		
		writeRegister(HMC5883_R_CONFA, 0x7C); // 8 samples averaged, 75Hz frequency, no artificial bias.
		writeRegister(HMC5883_R_CONFB, 0x00);
		writeRegister(HMC5883_R_MODE, 0x00);
		
		return true;
	}
	return false;
}

/**
* @param[in] mode The mode that you want the chip in.
*/
void HMC5883::setMode(unsigned char mode)
{
	if (mode > 2) {return;} //modes above two are invalid
  
	writeRegister(HMC5883_R_MODE, mode);
	delay(100);
}

/**
* @param[in] rate Change the data output rate. Value from 0-6 (6 being fastest?)
*/
void HMC5883::setRate(unsigned char rate)
{
	if (rate>6){return;}
	
	writeRegister(HMC5883_R_CONFA,rate<<2);
}

/**
* @param[in] gain Set the gain. Value from 0-7 (0 is most sensitive).
*/
void HMC5883::setGain(unsigned char gain)
{ 
	// 0-7, 1 default
	if (gain > 7) return;
	writeRegister(HMC5883_R_CONFB, gain << 5);
	_gain = gain;
}

/**
*@param[in,out] *x Pointer to where you want the x component of the reading.
*@param[in,out] *y Pointer to where you want the y component of the reading.
*@param[in,out] *z Pointer to where you want the z component of the reading.
*/
void HMC5883::getValues(int *x,int *y,int *z)
{
	float fx,fy,fz;
	getValues(&fx,&fy,&fz);
	*x= (int) (fx + 0.5);
	*y= (int) (fy + 0.5);
	*z= (int) (fz + 0.5);
}

/**
*@param[in,out] *x Pointer to where you want the x component of the reading.
*@param[in,out] *y Pointer to where you want the y component of the reading.
*@param[in,out] *z Pointer to where you want the z component of the reading.
*/
void HMC5883::getValues(float *x,float *y,float *z)
{
	int xr,yr,zr;
  
	getRaw(&xr, &yr, &zr);
	*x= ((float) xr) / x_scale;
	*y = ((float) yr) / y_scale;
	*z = ((float) zr) / z_scale;
}

/**
*@param[in,out] *xyz Pointer to where you want the xyz raw values.
*/
void HMC5883::getValues(float *xyz)
{
	getValues(&xyz[0], &xyz[1], &xyz[2]);
}

/**
*@param[out] *x Pointer to where you want the x raw value.
*@param[out] *y Pointer to where you want the y raw value.
*@param[out] *z Pointer to where you want the z raw value.
*/
void HMC5883::getRaw(int *x,int *y,int *z)
{
	Wire.beginTransmission(HMC5883_ADDR);
	Wire.write(HMC5883_R_XM); // will start from DATA X MSB and fetch all the others
	Wire.endTransmission();
  
	Wire.requestFrom(HMC5883_ADDR, 6);
	
	if(6 == Wire.available())
	{
		// read out the 3 values, 2 bytes each.
		*x = (int16_t)((Wire.read() << 8) | Wire.read());
		*z = (int16_t)((Wire.read() << 8) | Wire.read());// the Z registers comes before the Y registers in the HMC5883L
		*y = (int16_t)((Wire.read() << 8) | Wire.read());
		
		// the HMC5883 will automatically wrap around on the next request
	}
	
	if ((*x == -4096 || *y == -4096 || *z == -4096) && _gain < 7)
	{
		_gain += 1;
		setGain(_gain);
	}
}

/**
*@param[in] x X magnetometer value.
*@param[in] y Y magnetometer value.
*@param[out] Heading Heading obtained from x and y sensor values in degrees
*/
float HMC5883::getHeading(int x, int y)
{	
	return (atan2(y, x) + M_PI) * 180/M_PI;
}

/**
*@param[in] x X magnetometer value.
*@param[in] y Y magnetometer value.
*@param[out] Heading Heading obtained from x and y sensor values in radians
*/
float HMC5883::getHeadingRadians(int x, int y)
{	
	return (atan2(y, x) + M_PI);
}

/**
*@param[in] x X magnetometer value.
*@param[in] y Y magnetometer value.
*@param[in] z Z magnetometer value.
*@param[in] pitch  Pitch angle in degrees.
*@param[in] roll Y Roll angle in degrees.
*@param[out] Heading Tilt compensated heading value
*/
float HMC5883::getTiltCompensatedHeading(int x, int y, int z, float pitch, float roll)
{
	float pitch_rad = pitch * (M_PI / 180);
	float roll_rad = roll * (M_PI / 180);
	
	int xH = x * cos(pitch_rad) + z * sin(pitch_rad);
	int yH = x * sin(roll_rad) * sin(pitch_rad) + y * cos(roll_rad) - z * sin(roll_rad) * cos(pitch_rad);
	
	return (atan2(yH, xH) + M_PI) * 180/M_PI;
}

/**
*@param[in] x X magnetometer value.
*@param[in] y Y magnetometer value.
*@param[in] z Z magnetometer value.
*@param[in] pitch  Pitch angle in radians.
*@param[in] roll Y Roll angle in radians.
*/
float HMC5883::getTiltCompensatedHeadingRadians(int x, int y, int z, float pitch, float roll)
{	
	int xH = x * cos(pitch) + z * sin(pitch);
	int yH = x * sin(roll) * sin(pitch) + y * cos(roll) - z * sin(roll) * cos(pitch);
	
	return (atan2(yH, xH) + M_PI);
}

/*! 
	\brief Retrieve the value of the three ID registers.    
	Note:  Both the HMC5843 and HMC5883L have the same 'H43' identification register values. (Looks like someone at Honeywell screwed up.)
	\param id [out] Returns the three id register values.
*/
void HMC5883::getID(char id[3]) 
{
	Wire.beginTransmission(HMC5883_ADDR);
	Wire.write(HMC5883_R_IDA);             // Will start reading registers starting from Identification Register A.
	Wire.endTransmission();
	
	Wire.requestFrom(HMC5883_ADDR, 3);
	
	if(3 == Wire.available()) 
	{
		id[0] = Wire.read();
		id[1] = Wire.read();
		id[2] = Wire.read();
	}
	else
	{
		id[0]=0;  
		id[1]=0;
		id[2]=0;
	}
	Wire.endTransmission();
}

/** \brief Reads the Data Ready register to dtermine if new data is available to be read from the sensor

	\param[out] True/False returns True if new data is available to be read from the sensor
**/
bool HMC5883::getDataReady()
{
	Wire.beginTransmission(HMC5883_ADDR);
	Wire.write(0x09);
	Wire.endTransmission();
	
	Wire.requestFrom(HMC5883_ADDR, 1);
	
	return Wire.read() == 17;
}

/** \brief Reads the Data Ready register to dtermine if new data is available to be read from the sensor

	\param[out] Gain A value from 0-7 (0 being most sensitive, 7 being least sensitive) representing the sensor sensitivity
**/
uint8_t HMC5883::getGain()
{
	return _gain;
}

void HMC5883::writeRegister(unsigned char reg, unsigned char val)
{
	Wire.beginTransmission(HMC5883_ADDR);
	Wire.write(reg);        // send register address
	Wire.write(val);        // send value to write
	Wire.endTransmission(); //end transmission
}