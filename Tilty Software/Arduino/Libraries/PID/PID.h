/*
MPL3115A2.h - A easy to use interface for the MPL3115A2 Altimeter from Freescale Semiconductor
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

/*
This is a library to simplify the coding of PID control loops
*/

#ifndef PID_h
#define PID_h

#include "WProgram.h"
#include "Arduino.h"

#define DEBUG_PID

#define USE_TIME

class PID {
	public:
	//	constructors
	PID();
	
	//	Functions
	float update(int _var);
	float update(float _var);
	
	//	PID scalars
	float kP = 0;
	float kI = 0;
	float kD = 0;
	
	//	PID values
	float Pvalue = 0;
	float Ivalue = 0;
	float Dvalue = 0;
	
	//	PID limits
		//	P limits
	float upperPlimit = 2147483647;
	float lowerPlimit = -2147483647;
		//	I limits
	float upperIlimit = 2147483647;
	float lowerIlimit = -2147483647;
		//	D limits
	float upperDlimit = 2147483647;
	float lowerDlimit = -2147483647;
	
	private:
	//	Functions
	#ifdef DEBUG_PID
		void _serialDebug();
	#endif
	
	//	Loop timer
	float _dT = 1;
	long _timer;
	float _old_value;
};

#endif