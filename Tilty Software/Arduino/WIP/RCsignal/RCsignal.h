/*
This is a library to read an R/C PWM signal
*/

#include "Arduino.h"
#include <inttypes.h>

// ensure this library description is only included once
#ifndef RCsignal_h
#define RCsignal_h

// library interface description
class RCsignal {
  public:
    // constructors:
    RCsignal(uint8_t pin, void (*userfunc)(void));
    RCsignal(uint8_t pin, int *_outputVar);
    
    //	read function for reading value to other code
    int read();

	//	Returns library version
    int version(void);
    
  private:
  	//	setup interrupt
  	int readSignal();
  	
  	//	Timer variables
  	volatile boolean state;
  	volatile unsigned long _start;
  	volatile uint16_t _value;
  	
  	//	Interrupt pin number
  	uint8_t _pin;
  	
  	//	Output variable
  	int *_output;
};

#endif

