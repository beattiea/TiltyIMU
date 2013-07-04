/*
MPL3115A2.cpp - A easy to use interface for the MPL3115A2 Altimeter from Freescale Semiconductor
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "WProgram.h"
#include "Arduino.h"
#include "MPL3115A2.h"

MPL3115A2::MPL3115A2()
{
	//	Do nothing
}



//	Checks to see that the altimeter is connected and functional
//	and sets up the control registers
boolean MPL3115A2::init()
{
		#if defined(__AVR__) // only valid on AVR, not on 32bit platforms (eg: Arduino 2, Teensy 3.0)
	    TWBR = ((F_CPU / 400000L) - 16) / 2; // see twi_init in Wire/utility/twi.c
	#elif defined(__arm__)
		#if defined(CORE_TEENSY) && F_BUS == 48000000
			I2C0_F = 0x1A;  // Teensy 3.0 at 48 or 96 MHz
	  		I2C0_FLT = 4;
		#elif defined(CORE_TEENSY) && F_BUS == 24000000
			I2C0_F = 0x45;  // Teensy 3.0 at 24 MHz
			I2C0_FLT = 2;
		#endif
	#endif
	
	if (read(0x0C))
	{  
		// CTRL_REG1 (0x26): enable sensor, oversampling x128, altimeter mode 
  		write(0x26, 0xB9);
  		// CTRL_REG4 (0x29): Data ready interrupt enbabled
 		write(0x29, 0x80);
 		// PT_DATA_CFG (0x13): enable both pressure and temp event flags 
		write(0x13, 0x07);
		
		return true;
	}
	else
	{	return false;}
}



//  Resets the altimeter via software
void MPL3115A2::reset()
{
	write(0x26, 0x04);
}



//  Checks INT_SOURCE register to see if new data is available
boolean MPL3115A2::checkData()
{
	if(read(0x12) & 0x80) 
	{	return true;}
	else 
	{	return false;}
}



//	Reads the current altitude in meters
float MPL3115A2::readAltitudeM()
{
	int u_altitude, m_altitude;
	float l_altitude;
	
	u_altitude = read(0x01) << 8;//  The upper 8 bits of the altitude
	m_altitude = read(0x02);//  The middle 8 bits of the altitude
	l_altitude = float(read(0x03) >> 4) / 16.0;//  The lower 4 bits of the altitude
	
	return float(u_altitude | m_altitude) + l_altitude;
}



//	Reads the current altitude in feet
float MPL3115A2::readAltitudeF() 
{
	return 3.381 * readAltitudeM();
}



//	Reads the current temperature in degrees C
float MPL3115A2::readTempC()
{
	int u_temp;
	float l_temp;
	
	u_temp = read(0x04);//  Upper 8 bits of the temperature, representing the numbers before the decimal
	l_temp = float(read(0x05) >> 4) / 16.0;//  Lower 4 bits of the temperature, representing the numbers after the decimal
	
	return float(u_temp + l_temp);
}



//	Read the current temperature in degrees F
float MPL3115A2::readTempF() 
{
	return (readTempC() * 9) / 5.0 + 32;
}



//	Reads a byte on the sensor from the given address
byte MPL3115A2::read(byte _regAddr)
{
	Wire.beginTransmission(_addr);
	Wire.write(_regAddr);
	Wire.endTransmission(false);
	Wire.requestFrom(_addr, 1); // Request the data...
	return Wire.read();
}



//	Writes a byte of data to the sensor at the given address
byte MPL3115A2::write(byte _regAddr, byte _value)
{
	Wire.beginTransmission(_addr);
	Wire.write(_regAddr);
	Wire.write(_value);
	Wire.endTransmission(true);
}


