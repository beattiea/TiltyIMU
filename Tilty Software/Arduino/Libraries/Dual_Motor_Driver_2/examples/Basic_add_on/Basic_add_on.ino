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

#include "DualMotorDriver_2.h"
#include "Encoder.h"
#include "Wire.h"
#include "EEPROM.h"

// Included to ensure no compatibility errors
#include "RCadapter.h"
#include "SatelliteRX.h"
#include "Servo.h"
//===========================================

MotorDriver motors;

int motor1 = 0;
int motor2 = 0;
uint16_t count = 0;

void setup() {
	motors.init();
	
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
}

int power = 0;

void loop() {
	// Purely testing code, everything else is handled by interrupt routines
}


void receiveEvent(int bytes) {
	motors.getData(bytes);
}

void requestEvent() {
	motors.sendData();
}

ISR(TIMER2_OVF_vect) {
	motors.update();
	
	TCNT2 = 130;
	TIFR2 = 0x00;
}