/*
This example program will read an RC signal input from pin 13 to a variable.
This program currently only works on the Teensy 3.0
*/

#include <RCsignal.h>

RCsignal pwm(13, readChannel1);

RCsignal channel1(4, readChannel1);

volatile int value = 0;

void setup() {
  Serial.begin(38400);
  while(!Serial) {}
}

void loop() {
  Serial.print("PWM time value: ");
  Serial.print(value);
  Serial.println();
}

void readChannel1() {
  //Serial.println("hello");
  value = pwm.read();
}