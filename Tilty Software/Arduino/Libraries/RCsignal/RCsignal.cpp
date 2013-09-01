#include "RCsignal.h"
#include "Arduino.h"
#include <inttypes.h>

RCsignal::RCsignal() {
	// Do nothing
}

RCsignal::RCsignal(uint8_t pin, void (*userfunc)(void)) {
	pinMode(pin, INPUT);
	attachInterrupt(pin, userfunc, CHANGE);
	state = digitalReadFast(pin);
	this->_pin = pin;
}

int RCsignal::read() {
	return readSignal();
}

int RCsignal::version() {
	return 0;
}

int RCsignal::readSignal() {
	if (!state) 
	{
		_start = micros();
	}
	else 
	{
		_value = micros() - _start;
	}
	
	state = !state;
	
	return _value;
}