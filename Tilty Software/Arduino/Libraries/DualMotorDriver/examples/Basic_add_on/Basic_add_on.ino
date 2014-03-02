/*
!!!!!!BEWARE!!!!!!
The FastPWM used by the motor driver changes the timer used by delay(), delayMicroseconds(), millis() and micros().
To correct for this change, multiply any delays you may want by 64 or divide any timers by 64.

For example:
To delay 10ms, use delay(640);
To read a timer, actual_timer_value = millis() / 64;

Or for a more permanent change, you can modify a line in the wiring.c function in the Arduino program files
hardware\arduino\cores\arduino\wiring.c
Change: #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
to
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(256))

However this is a global change and will affect all Arduino code, not just this program.
*/

#include "DualMotorDriver.h"
//#include "Wire.h"
#include "EEPROM.h"

// Included to ensure no compatibility errors
//#include "RCadapter.h"
//#include "SatelliteRX.h"
#include "Servo.h"
//===========================================

void setup() {
	MotorDriver.init();
}


void loop() {
	// Purely testing code, everything else is handled by interrupt routines
}
