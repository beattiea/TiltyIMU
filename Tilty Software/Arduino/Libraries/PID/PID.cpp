#include <PID.h>

PID::PID()
{
	//	Do nothing
}

PID::~PID()
{
	//	Do nothing
}

/** This function initializes the PID object with P, I, and D value scalars.
* @param[in] kP Set the P value scalar.
* @param[in] kI Set the I value scalar.
* @param[in] kD Set the D value scalar.
*/ 
PID::PID(float _kP, float _kI, float _kD)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = FORWARD;
}

/** This function initializes the PID object with P, I, and D value scalars and a direction relative to the input (+/-).
* @param[in] kP Set the P value scalar.
* @param[in] kI Set the I value scalar.
* @param[in] kD Set the D value scalar.
* @param[in] dir Set the direction relative to the input value (+ input = + output or + input = - output).
*/ 
PID::PID(float _kP, float _kI, float _kD, bool _dir)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = _dir;
}

/** This function initializes the PID object with input and output variables so they will automatically update without needing to be set manually.
* @param[in] &inputVar A pointer to the input variable.
* @param[in] &outputVar A pointer to the output variable.
*/ 
PID::PID(float *_inputVar, float *_outputVar)
{
	_input = _inputVar;
	_output = _outputVar;
}

/** This function initializes the PID object with P, I, and D value scalars as well as input and output variables so they can automatically update without needing to be set manually.
* @param[in] &inputVar A pointer to the input variable.
* @param[in] &outputVar A pointer to the output variable.
* @param[in] kP Set the P value scalar.
* @param[in] kI Set the I value scalar.
* @param[in] kD Set the D value scalar.
*/ 
PID::PID(float *_inputVar, float *_outputVar, float _kP, float _kI, float _kD)
{
	_input = _inputVar;
	_output = _outputVar;
	
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = FORWARD;
}

/** This function initializes the PID object with P, I, and D value scalars as well as input and output variables so they can automatically update without needing to be set manually, and a direction relative to the input value.
* @param[in] &inputVar A pointer to the input variable.
* @param[in] &outputVar A pointer to the output variable.
* @param[in] kP Set the P value scalar.
* @param[in] kI Set the I value scalar.
* @param[in] kD Set the D value scalar.
* @param[in] dir Set the direction relative to the input value (+ input = + output or + input = - output).
*/ 
PID::PID(float *_inputVar, float *_outputVar, float _kP, float _kI, float _kD, bool _dir)
{
	_input = _inputVar;
	_output = _outputVar;
	
	kP = _kP;
	kI = _kI;
	kD = _kD;
	
	_direction = _dir;
}

/** Call this function to update the PID output. Needs to have a input variable set in the constructor to work.
*/ 
float PID::update()
{
	*_output = update(*_input);
	return *_output;
}

/** Call this function to update the PID output.
* @param[in] value The integer input value that the PID will update using.
*/ 
float PID::update(int _value)
{	
	return update(float(_value));
}

/** Call this function to update the PID output.
* @param[in] value The float input value that the PID will update using.
*/ 
float PID::update(float _value)
{	
	#ifdef USE_TIME
		_dT = (millis() - _timer) / 1000.0;
		_timer = millis();
		if (_dT == 0) { _dT++;}
	#endif
	
	_value = checkInputOK(_value);
	
	if (_value == -214783647)
	{
		return constrain(Pvalue + Ivalue + Dvalue, lowerLimit, upperLimit);
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

/** Set the scalar values of the P, I, and D values.
* @param[in] kP Set the P value scalar.
* @param[in] kI Set the I value scalar.
* @param[in] kD Set the D value scalar.
*/ 
void PID::setScalars(float _kP, float _kI, float _kD)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
}

/** Sets the overall output limits of the PID values. The output value will not exceed these values.
* @param[in] lower Set the lower output limit.
* @param[in] upper Set the upper output limit.
*/ 
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

/** Sets the output limits of the P value. The output proportional value will not exceed these values.
* @param[in] lower Set the lower output limit.
* @param[in] upper Set the upper output limit.
*/ 
void PID::setPLimits(float _lower, float _upper)
{
	upperPLimit = _upper;
	lowerPLimit = _lower;
}

/** Sets the output limits of the I value. The output integral value will not exceed these values.
* @param[in] lower Set the lower output limit.
* @param[in] upper Set the upper output limit.
*/ 
void PID::setILimits(float _lower, float _upper)
{
	upperILimit = _upper;
	lowerILimit = _lower;
}

/** Sets the output limits of the D value. The output derivative value will not exceed these values.
* @param[in] lower Set the lower output limit.
* @param[in] upper Set the upper output limit.
*/ 
void PID::setDLimits(float _lower, float _upper)
{
	upperDLimit = _upper;
	lowerDLimit = _lower;
}

/** Sets the direction of the output value relative to the input value. Can be set to FORWARD or REVERSE.
* @param[in] dir Set the direction relative to the input value (+ input = + output or + input = - output).
*/
void PID::setDirection(bool _dir)
{
	_direction = _dir;
}

/** Sets the input values that will trigger the PID values to update. An update will only occur if the input variable exceeds the range defined by these values.
* @param[in] lower Set the lower input trigger limit.
* @param[in] upper Set the upper input trigger limit.
*/ 
void PID::setInputTriggers(float _lower, float _upper)
{
	upperInputTrigger = _upper;
	lowerInputTrigger = _lower;
}

/** Sets the input value constraints that will prevent the PID values from updating. An update will only occur if the input variable is within the range defined by these values.
* @param[in] lower Set the lower input value constraint.
* @param[in] upper Set the upper input value constraint.
*/ 
void PID::setInputConstraints(float _lower, float _upper)
{
	upperInputConstraint = _upper;
	lowerInputConstraint = _lower;
}

/** Resets the P, I, and D values to zero, without affecting the scalars. This does not update the output variable if it has been set.
*/ 
void PID::reset()
{
	Pvalue = 0;
	Ivalue = 0;
	Dvalue = 0;
}

/** Returns true if the combined PID values exceed the upper or lower output limits.
*/ 
bool PID::limited() { return (Pvalue + Ivalue + Dvalue >= upperLimit || Pvalue + Ivalue + Dvalue <= lowerLimit) ? true : false;}

/** Returns true if the P value exceeds the upper or lower P output limits.
*/ 
bool PID::PLimited() { return (Pvalue >= upperPLimit || Pvalue <= lowerPLimit) ? true : false;}

/** Returns true if the D value exceeds the upper or lower D output limits.
*/ 
bool PID::ILimited() { return (Ivalue >= upperILimit || Ivalue <= lowerILimit) ? true : false;}

/** Returns true if the D value exceeds the upper or lower D output limits.
*/ 
bool PID::DLimited() { return (Dvalue >= upperDLimit || Dvalue <= lowerDLimit) ? true : false;}

/** Returns 1 if direction is set to forward, -1 if driection is set to reverse.
*/ 
int8_t PID::getDirection() { return _direction ? 1 : -1;}

/** Returns P value scalar. */
float PID::getkP() { return kP;}
/** Returns I value scalar. */
float PID::getkI() { return kI;}
/** Returns D value scalar. */
float PID::getkD() { return kD;}



float PID::checkInputOK(float _value)
{
	if (_value >= upperInputTrigger)
	{
		if (_value <= upperInputConstraint && _value >= lowerInputConstraint)
		{
			return _value - upperInputTrigger;
		}
	}
	else if (_value <= lowerInputTrigger)
	{
		if (_value <= upperInputConstraint && _value >= lowerInputConstraint)
		{
			return _value - lowerInputTrigger;
		}
	}
	
	return -214783647;
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