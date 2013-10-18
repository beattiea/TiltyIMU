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

void setup() {
	motors.init();
	
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
}

uint8_t enc1;
uint8_t enc2;
uint8_t enc3;
uint8_t enc4;
uint8_t enc5, enc6, enc7, enc8;

void loop() {
	motors.update();// This function should be called as frequently as possible to keep everything up to speed
}

void receiveEvent(int bytes) {
	motors.getData(bytes);
	//digitalWrite(10, HIGH);
}

void requestEvent() {
	motors.sendData();
	//digitalWrite(10, LOW);
}