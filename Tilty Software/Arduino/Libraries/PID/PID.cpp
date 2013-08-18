#include <PID.h>

PID::PID()
{
	//	Do nothing
}

PID::~PID()
{
	//	Do nothing
}

PID::PID(float _kP, float _kI, float _kD)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = FORWARD;
}

PID::PID(float _kP, float _kI, float _kD, bool _dir)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = _dir;
}

PID::PID(float *_inputVar, float *_outputVar)
{
	_input = _inputVar;
	_output = _outputVar;
}

PID::PID(float *_inputVar, float *_outputVar, float _kP, float _kI, float _kD)
{
	_input = _inputVar;
	_output = _outputVar;
	
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = FORWARD;
}

PID::PID(float *_inputVar, float *_outputVar, float _kP, float _kI, float _kD, bool _dir)
{
	_input = _inputVar;
	_output = _outputVar;
	
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = _dir;
}



float PID::update()
{
	*_output = update(*_input);
	return *_output;
}

float PID::update(int _value)
{	
	return update(float(_value));
}

float PID::update(float _value)
{	
	#ifdef USE_TIME
		_dT = (millis() - _timer) / 1000.0;
		_timer = millis();
		if (_dT == 0) _dT++;
	#endif
	
	_value = checkInputOK(_value);
	
	if (_value == 0)
	{
		reset();
	}
	
	if (_direction)
	{
		Pvalue = constrain(kP * _value, lowerPLimit, upperPLimit);
		Ivalue = constrain(Ivalue + kI * _value * _dT, lowerILimit, upperILimit);
		Dvalue = constrain((kD * (_value - _old_value)) / _dT, lowerDLimit, upperDLimit);
	}
	
	if (!_direction)
	{
		Pvalue = -constrain(kP * _value, lowerPLimit, upperPLimit);
		Ivalue = constrain(Ivalue - kI * _value * _dT, lowerILimit, upperILimit);
		Dvalue = -constrain((kD * (_value - _old_value)) / _dT, lowerDLimit, upperDLimit);
	}

	_old_value = _value;
	
	#ifdef DEBUG_PID
		_serialDebug();
	#endif
	
	return constrain(Pvalue + Ivalue + Dvalue, lowerLimit, upperLimit);
}



void PID::setScalars(float _kP, float _kI, float _kD)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
}



void PID::setLimits(float _lower, float _upper)
{
	upperLimit = _upper;
	lowerLimit = _lower;
	
	if (upperPLimit > _upper) upperPLimit = _upper;
	if (lowerPLimit < _lower) lowerPLimit = _lower;
	
	if (upperILimit > _upper) upperILimit = _upper;
	if (lowerILimit < _lower) lowerILimit = _lower;
	
	if (upperDLimit > _upper) upperDLimit = _upper;
	if (lowerDLimit < _lower) lowerDLimit = _lower;
}

void PID::setPLimits(float _lower, float _upper)
{
	upperPLimit = _upper;
	lowerPLimit = _lower;
}

void PID::setILimits(float _lower, float _upper)
{
	upperILimit = _upper;
	lowerILimit = _lower;
}

void PID::setDLimits(float _lower, float _upper)
{
	upperDLimit = _upper;
	lowerDLimit = _lower;
}



void PID::setInputTriggers(float _lower, float _upper)
{
	upperInputTrigger = _upper;
	lowerInputTrigger = _lower;
}

void PID::setInputConstraints(float _lower, float _upper)
{
	upperInputConstraint = _upper;
	lowerInputConstraint = _lower;
}



void PID::reset()
{
	Pvalue = 0;
	Ivalue = 0;
	Dvalue = 0;
}



bool PID::limited() { return (Pvalue + Ivalue + Dvalue >= upperLimit || Pvalue + Ivalue + Dvalue <= lowerLimit) ? true : false;}



int8_t PID::getDirection() { return _direction ? 1 : -1;}
float PID::getkP() { return kP;}
float PID::getkI() { return kI;}
float PID::getkD() { return kD;}



float PID::checkInputOK(float _value)
{
	if (_value >= upperInputTrigger)
	{
		if (_value <= upperInputConstraint || _value >= lowerInputConstraint)
		{
			return _value - upperInputTrigger;
		}
	}
	else if (_value <= lowerInputTrigger)
	{
		if (_value <= upperInputConstraint || _value >= lowerInputConstraint)
		{
			return _value - lowerInputTrigger;
		}
	}
	
	return 0;
}


#ifdef DEBUG_PID
	void PID::_serialDebug()
	{
		Serial.print("\nP: ");
		Serial.print(Pvalue);
		Serial.print("\tI: ");
		Serial.print(Ivalue);
		Serial.print("\tD: ");
		Serial.print(Dvalue);
	
		#ifdef USE_TIME
			Serial.print("\tdT: ");
			Serial.println(_dT, 3);
		#else
			Serial.println();
		#endif
	}
#endif