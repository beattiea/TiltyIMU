/*
PID.h - A easy to use interface for creating and calculating values for a PID control loop
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 2.5 GNU General Public License as
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

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef PID_h
#define PID_h

//#define DEBUG_PID
#define USE_TIME

#define FORWARD true
#define REVERSE false

class PID {
	public:
	//	constructors
	PID();
	~PID();
	PID(float _kP, float _kI, float _kD);
	PID(float _kP, float _kI, float _kD, bool _dir);
	PID(float *_inputVar, float *_outputVar);
	PID(float *_inputVar, float *_outputVar, float _kP, float _kI, float _kD);
	PID(float *_inputVar, float *_outputVar, float _kP, float _kI, float _kD, bool _dir);
	
	//	Functions
		//	Updates the PID loop
	float update();
	float update(int _var);
	float update(float _var);
	
		//	Sets the PID scalar values
	void setScalars(float _kP, float _kI, float _kD);
	
		//	Sets the PID output limits
	void setLimits(float _lower, float _upper);
	void setPLimits(float _lower, float _upper);
	void setILimits(float _lower, float _upper);
	void setDLimits(float _lower, float _upper);
	void setDirection(bool _dir);
	
		//	Sets the PID input limits
	void setInputTriggers(float _lower, float _upper);
	void setInputConstraints(float _lower, float _upper);
	
		//	Resets the PID values, needs to be followed by an update
	void reset();
	
		//	Check whether PID has exceeded its limited values
	bool limited();
	bool PLimited();
	bool ILimited();
	bool DLimited();
	
		//	Display PID settings functions
	int8_t getDirection();
	float getkP();
	float getkI();
	float getkD();
	
	//	PID scalars
	float kP = 0;
	float kI = 0;
	float kD = 0;
	
	//	PID values
	float Pvalue = 0;
	float Ivalue = 0;
	float Dvalue = 0;
	
	//	PID limits
		//	Overall limits
	float upperLimit = 2147483647;
	float lowerLimit = -2147483647;
		//	P limits
	float upperPLimit = 2147483647;
	float lowerPLimit = -2147483647;
		//	I limits
	float upperILimit = 2147483647;
	float lowerILimit = -2147483647;
		//	D limits
	float upperDLimit = 2147483647;
	float lowerDLimit = -2147483647;
	
	//	Input limits
		//	PID input trigger limits
	float upperInputTrigger = 0.0;
	float lowerInputTrigger = 0.0;
		//	PID input constraint limits
	float upperInputConstraint = 2147483647;
	float lowerInputConstraint = -214783647;
	
	private:
	//	Functions
	float checkInputOK(float _value);
	#ifdef DEBUG_PID
		void _serialDebug();
	#endif
		
	//	Loop timer
	double _dT = 1;
	unsigned long _timer;
	float _old_value;
	
	//	Variable storage
	float *_input;
	float *_output;
	
	//	Other private variables
	bool _direction = true;
};

#endif