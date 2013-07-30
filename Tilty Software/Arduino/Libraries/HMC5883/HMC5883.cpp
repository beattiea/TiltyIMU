#include "HMC5883.h"

//milligauss per gain for self test current bias
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
  
HMC5883::HMC5883()
{
	x_scale = (float) 1.0;
	y_scale = (float) 1.0;
	z_scale = (float) 1.0;
}

bool HMC5883::init(bool mode)
{
	if(mode)
	{
		setMode(0);
	}
	
	delay(5); //we need some time for the chip to power on
	
	writeRegister(HMC58X3_R_CONFA, 0x70); // 8 samples averaged, 75Hz frequency, no artificial bias.
	writeRegister(HMC58X3_R_CONFB, 0xA0);
	writeRegister(HMC58X3_R_MODE, 0x00);
}

void HMC5883::setMode(unsigned char mode)
{
	if (mode > 2) {return;} //modes above two are invalid
  
	writeRegister(HMC58X3_R_MODE, mode);
	delay(100);
}

void HMC5883::setDOR(unsigned char DOR) {
	if (DOR>6){return;}
	writeRegister(HMC58X3_R_CONFA,DOR<<2);
}


void HMC5883::setGain(unsigned char gain) { 
	// 0-7, 1 default
	if (gain > 7) return;
	writeRegister(HMC58X3_R_CONFB, gain << 5);
}


void HMC5883::writeRegister(unsigned char reg, unsigned char val)
{
	Wire.beginTransmission(HMC58X3_ADDR);
	Wire.write(reg);        // send register address
	Wire.write(val);        // send value to write
	Wire.endTransmission(); //end transmission
}


void HMC5883::getValues(int *x,int *y,int *z)
{
	float fx,fy,fz;
	getValues(&fx,&fy,&fz);
	*x= (int) (fx + 0.5);
	*y= (int) (fy + 0.5);
	*z= (int) (fz + 0.5);
}


void HMC5883::getValues(float *x,float *y,float *z)
{
	int xr,yr,zr;
  
	getRaw(&xr, &yr, &zr);
	*x= ((float) xr) / x_scale;
	*y = ((float) yr) / y_scale;
	*z = ((float) zr) / z_scale;
}


void HMC5883::getRaw(int *x,int *y,int *z)
{
	Wire.beginTransmission(HMC58X3_ADDR);
	Wire.write(HMC58X3_R_XM); // will start from DATA X MSB and fetch all the others
	Wire.endTransmission();
  
	Wire.beginTransmission(HMC58X3_ADDR);
	Wire.requestFrom(HMC58X3_ADDR, 6);
	if(6 == Wire.available())
	{
		// read out the 3 values, 2 bytes each.
		*x = (int16_t)((Wire.read() << 8) | Wire.read());
		// the Z registers comes before the Y registers in the HMC5883L
		*z = (int16_t)((Wire.read() << 8) | Wire.read());
		*y = (int16_t)((Wire.read() << 8) | Wire.read());
		
		// the HMC58X3 will automatically wrap around on the next request
	}
	Wire.endTransmission();
}


void HMC5883::getValues(float *xyz)
{
	getValues(&xyz[0], &xyz[1], &xyz[2]);
}

/*! 
	\brief Retrieve the value of the three ID registers.    

	Note:  Both the HMC5843 and HMC5883L have the same 'H43' identification register values. (Looks like someone at Honeywell screwed up.)

	\param id [out] Returns the three id register values.
*/
void HMC5883::getID(char id[3]) 
{
	Wire.beginTransmission(HMC58X3_ADDR);
	Wire.write(HMC58X3_R_IDA);             // Will start reading registers starting from Identification Register A.
	Wire.endTransmission();
  
	Wire.beginTransmission(HMC58X3_ADDR);
	Wire.requestFrom(HMC58X3_ADDR, 3);
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