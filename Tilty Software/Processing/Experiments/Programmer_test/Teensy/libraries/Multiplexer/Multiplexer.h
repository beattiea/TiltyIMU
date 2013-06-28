/*
This is a library to simplify control of the sparkfun 16 channel analog multiplexer
*/

#include "WProgram.h"

// ensure this library description is only included once
#ifndef Multiplexer_h
#define Multiplexer_h

//#define MUX_DEBUG	// Uncomment to enable debugging. Doesn't currently do anything

#define DIGITAL_IN 0
#define DIGITAL_OUT 1
#define ANALOG_IN 2
#define ANALOG_OUT 3

// library interface description
class Multiplexer {
  public:
    // constructors:
    Multiplexer(int low_pin, int signal_pin);
    //Multiplexer(int low_pin, int signal_pin, settings);
    Multiplexer(int bit_0_pin, int bit_1_pin, int bit_2_pin, int bit_3_pin, int signal_pin);
    Multiplexer(int bit_0_pin, int bit_1_pin, int bit_2_pin, int bit_3_pin, int signal_pin, int settings[]);

    //	Read methods
    int muxDigitalRead(int multiplex_pin);
    int muxAnalogRead(int multiplex_pin);
    int readPin(int multiplex_pin);
    
    //	Write methods
    void muxDigitalWrite(int multiplex_pin, int value);
    void muxAnalogWrite(int multiplex_pin, int value);
    void writeAll(int mux_write_array[16], long delay);
    
    //	Setup method
    void muxPinMode(int mux_pin, int mode);

	//	Returns library version
    int version(void);
    #ifndef _muxPinSettings
    	int _muxPinSettings[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//  Last number is current state
    #endif
    int _muxPinValues[16];

  private:
  	//	Setup function
  	void setupPins();
  	
    //	Calculator function
    void setBits(int multiplex_pin);
    
    //	Check function
    void checkSignalPin(int mux_pin);
    
    int value;// Value to write to the signal pin
    int multiplex_pin;//	Pin on the multplexer to write to
    
    //	Pin variables
    int channel_pins[5];
};

#endif

