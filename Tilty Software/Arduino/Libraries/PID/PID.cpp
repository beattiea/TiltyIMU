#include <PID.h>

PID::PID()
{
	
}

float PID::update(int _value)
{
	#ifdef USE_TIME
		_dT = (millis() - _timer) / 1000.0;
		_timer = millis();
	#endif
	
	Pvalue = constrain(kP * _value, lowerPlimit, upperPlimit);
	Ivalue = constrain(Ivalue + kI * _value * _dT, lowerIlimit, upperIlimit);
	Dvalue = constrain((kD * (_value - _old_value)) / _dT, lowerDlimit, upperDlimit);
	
	_old_value = _value;
	
	#ifdef DEBUG_PID
		_serialDebug();
	#endif
}

float PID::update(float _value)
{
	#ifdef USE_TIME
		_dT = (millis() - _timer) / 1000.0;
		_timer = millis();
	#endif
	
	Pvalue = constrain(kP * _value, lowerPlimit, upperPlimit);
	Ivalue = constrain(Ivalue + kI * _value * _dT, lowerIlimit, upperIlimit);
	Dvalue = constrain((kD * (_value - _old_value)) / _dT, lowerDlimit, upperDlimit);
	
	_old_value = _value;
	
	#ifdef DEBUG_PID
		_serialDebug();
	#endif
}

void PID::_serialDebug()
{
	Serial.print("P: ");
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