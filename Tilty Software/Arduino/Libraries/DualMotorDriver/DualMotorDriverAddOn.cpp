/*
DualMotorDriver.cpp - Software library to program and control the TiltyIMU Dual Motor Driver Shield
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 2 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef __MK20DX128__

#include "DualMotorDriverAddOn.h"


DualMotorDriver MotorDriver;

// Teensy master control code
DualMotorDriver::DualMotorDriver()
{	
	I2C_bus = 1;
}

DualMotorDriver::DualMotorDriver(uint8_t bus)
{	
	if (bus) I2C_bus = 1;
	else I2C_bus = 0;
}

DualMotorDriver::~DualMotorDriver() 
{
	// Do nothing
}


// Called to initialize the motor driver ISR's
void DualMotorDriver::init()
{
	
}

// Sets the I2C bus pins on the Teensy to the bus used by the motor driver
inline void DualMotorDriver::setI2Cpins()
{
	if (I2C_bus)
	{
		if (CORE_PIN16_CONFIG != I2C_config) setI2Cpins1617();
	}
	else 
	{
		if (CORE_PIN18_CONFIG != I2C_config) setI2Cpins1819();
	}
}

// Sets the I2C bus pins on the Teensy to 18 and 19
inline void DualMotorDriver::setI2Cpins1819()
{
    CORE_PIN18_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN19_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(16) = 0; // input
    CORE_PIN16_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(17) = 0; // input
    CORE_PIN17_CONFIG = PORT_PCR_MUX(1);
}

// Sets the I2C bus pins on the Teensy to 16 and 17
inline void DualMotorDriver::setI2Cpins1617()
{
    CORE_PIN16_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN17_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(18) = 0; // input
    CORE_PIN18_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(19) = 0; // input
    CORE_PIN19_CONFIG = PORT_PCR_MUX(1);
}


// Takes a pointer to a variable and reads a new value into it from I2C
inline void DualMotorDriver::wireToVar(uint8_t *var)
{
	*var = Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
inline void DualMotorDriver::wireToVar(uint16_t *var)
{
	*var = ((int16_t)Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
inline void DualMotorDriver::wireToVar(int32_t *var)
{
	*var = ((int32_t)Wire.read() << 24) | ((int32_t)Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
inline void DualMotorDriver::wireToVar(float *var)
{
	data_union.bytes[0] = Wire.read();
	data_union.bytes[1] = Wire.read();
	data_union.bytes[2] = Wire.read();
	data_union.bytes[3] = Wire.read();
	//*var = (Wire.read() << 24) | (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
	*var = data_union.float32;
}
// ========== End of class ==========
#endif