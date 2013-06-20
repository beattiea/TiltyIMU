#include "WProgram.h"
#include "Arduino.h"
#include "Multiplexer.h"

//Takes only the pin number of the lowest channel bit and assumes
//that the next three pins are the next three bits. Also takes a specific
//signal pin number.
Multiplexer::Multiplexer(int low_pin, int signal_pin)
{
	for (int i = low_pin; i < low_pin + 4; i++)
	{
		this->channel_pins[i - low_pin] = i;
	}
	this->channel_pins[4] = signal_pin;
	
	setupPins();
}



//Takes a pin number for each channel bit. Also takes a specific 
//signal pin number.
Multiplexer::Multiplexer(int bit_0_pin, int bit_1_pin, int bit_2_pin, int bit_3_pin, int signal_pin)
{
	this->channel_pins[0] = bit_0_pin;
	this->channel_pins[1] = bit_1_pin;
	this->channel_pins[2] = bit_2_pin;
	this->channel_pins[3] = bit_3_pin;
	this->channel_pins[4] = signal_pin;
	
	setupPins();
}

Multiplexer::Multiplexer(int bit_0_pin, int bit_1_pin, int bit_2_pin, int bit_3_pin, int signal_pin, int settings[])
{
	this->channel_pins[0] = bit_0_pin;
	this->channel_pins[1] = bit_1_pin;
	this->channel_pins[2] = bit_2_pin;
	this->channel_pins[3] = bit_3_pin;
	this->channel_pins[4] = signal_pin;
	
	for (int i = 0; i < 16; i++)
	{
		_muxPinSettings[i] = settings[i];
	}
	
	setupPins();
}


//Sets up channel select pins as outputs
void Multiplexer::setupPins()
{
	pinMode(channel_pins[0], OUTPUT);
	pinMode(channel_pins[1], OUTPUT);
	pinMode(channel_pins[2], OUTPUT);
	pinMode(channel_pins[3], OUTPUT);
	pinMode(channel_pins[4], INPUT);
}

//Sets the pin mode of a multiplexed pin to one of the following:
//DIGITAL_IN, DIGITAL_OUT, ANALOG_IN, ANALOG_OUT.
void Multiplexer::muxPinMode(int mux_pin, int mode)
{
	#ifndef _muxPinSettings
	_muxPinSettings[mux_pin] = mode;
	#endif
}



//Reads a multiplexed pin as a digital value.
//Also sets the pin as a digital input if it isn't already.
int Multiplexer::muxDigitalRead(int mux_pin)
{
	if (_muxPinSettings[mux_pin] != DIGITAL_IN)
	{	return -1;}

	checkSignalPin(mux_pin);

	setBits(mux_pin);
	return digitalRead(this->channel_pins[4]);
}

//Reads a multiplexed pin as an analog value.
//Also sets the pin as a analog input if it isn't already.
int Multiplexer::muxAnalogRead(int mux_pin)
{
	if (_muxPinSettings[mux_pin] != ANALOG_IN)
	{	return -1;}

	checkSignalPin(mux_pin);
	
	setBits(mux_pin);
	return analogRead(this->channel_pins[4]);
}

//Takes a global array of length 16 and fills it with readings
//from all multiplexed pins defined as inputs.
int Multiplexer::readPin(int mux_pin)
{
	setBits(mux_pin);
	
	if (_muxPinSettings[mux_pin] == ANALOG_IN)
	{	return muxAnalogRead(mux_pin);}
	
	if (_muxPinSettings[mux_pin] == DIGITAL_IN)
	{	return muxDigitalRead(mux_pin);}
	
	return -1;
}




//Writes a digital value to a multiplexed pin.
//Also sets the pin as a digital output if it isn't already.
void Multiplexer::muxDigitalWrite(int mux_pin, int value)
{
	/*
	#ifndef _muxPinSettings
	if (_muxPinSettings[mux_pin] != DIGITAL_OUT)
	{
		pinMode(mux_pin, DIGITAL_OUT);
	}
	#endif
	
	checkSignalPin(mux_pin);
	*/
	setBits(mux_pin);
	digitalWrite(this->channel_pins[4], value);
}

//Writes a analog value to a multiplexed pin.
//Also sets the pin as a analog output if it isn't already.
void Multiplexer::muxAnalogWrite(int mux_pin, int value)
{
	/*
	#ifndef _muxPinSettings
	if (_muxPinSettings[mux_pin] != ANALOG_OUT)
	{
		pinMode(mux_pin, ANALOG_OUT);
	}
	#endif
	
	checkSignalPin(mux_pin);
	*/
	setBits(mux_pin);
	analogWrite(this->channel_pins[4], value);
}

//Takes a global array of length 16 and writes value in each
//slot to each pin set up as an output for the specified delay
//in microseconds
void Multiplexer::writeAll(int mux_write_array[16], long delay)
{
	for (int i = 0; i < 16; i++)
	{
		switch (_muxPinSettings[i])
		{
			case DIGITAL_OUT:
			digitalWrite(i, mux_write_array[i]);
			break;
			case ANALOG_OUT:
			analogWrite(i, mux_write_array[i]);
			break;
			default:
			break;
		}
		delayMicroseconds(delay);
	}
}



//Sets the channel selection pins based on the selected
//multiplexer pin.
void Multiplexer::setBits(int mux_pin)
{
	digitalWriteFast(channel_pins[0], ((mux_pin) >> (0)) & 0x01);
	digitalWriteFast(channel_pins[1], ((mux_pin) >> (1)) & 0x01);
	digitalWriteFast(channel_pins[2], ((mux_pin) >> (2)) & 0x01);
	digitalWriteFast(channel_pins[3], ((mux_pin) >> (3)) & 0x01);
}

//Checks to make sure that the signal pin's pinMode matches
//the set pinMode in _muxPinSettings
void Multiplexer::checkSignalPin(int mux_pin)
{
	if (_muxPinSettings[17] != _muxPinSettings[mux_pin] % 2)
	{
		switch (_muxPinSettings[17]) {
			case 0:
			pinMode(channel_pins[4], OUTPUT);
			break;
			case 1:
			pinMode(channel_pins[4], INPUT);
			break;
		}
	}
}



