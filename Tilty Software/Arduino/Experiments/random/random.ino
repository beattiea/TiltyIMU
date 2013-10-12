#include <SatelliteRX.h>
#include <RCadapter.h>

#include <Wire.h>
#include "EEPROM.h"

#include <Servo.h>
//#include <FastServo.h>

byte inputs[3] = {2, 3, 4};

RCadapter rx = RCadapter();

// Motor PWM pins
#define M1 6
#define M2 5
// Motor direction control pins
#define M1A 4
#define M1B 9
#define M2A 7
#define M2B 8

void setup() {
	/*	R/C adapter testing
	Serial.begin(115200);
	//delay(5000);
	Serial.println("Beginning...");
	rx.init();
	
	for (int i = 0; i < 3; i++) {
		Serial.print("input_pins: ");
		Serial.println(rx.input_pins[i]);
	}
	Serial.println();
	
	rx.initRCinputs(inputs, 3);
	
	for (int i = 0; i < 3; i++) {
		Serial.print("input_pins: ");
		Serial.println(rx.input_pins[i]);
	}
	Serial.println();
	*/
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);// Setup pins 5 and 6 for fast PWM
	TCCR0B = _BV(CS00);// Set PWM frequency to 62.5kHz (fastest possible)
	
	pinMode(M1, OUTPUT);
	pinMode(M2, OUTPUT);
	
	pinMode(M1A, OUTPUT);
	pinMode(M1B, OUTPUT);
	pinMode(M2A, OUTPUT);
	pinMode(M2B, OUTPUT);
	
	digitalWrite(M1A, HIGH);
	digitalWrite(M1B, LOW);
	digitalWrite(M2A, LOW);
	digitalWrite(M2B, HIGH);
}

void loop() {
	/*	R/C adapter testing
	if (rx.readRCinputs()) {
		for (int i = 0; i < 3; i++) {
			Serial.print("Channel: ");
			Serial.println(rx.channel_values[i]);
		}
		Serial.println();
	}
	*/
	
	for (int i = 0; i < 256; i++) {
		analogWrite(M1, i);
		analogWrite(M2, i);
		delay(160);
	}
	
	for (int i = 255; i > -1; i--) {
		analogWrite(M1, i);
		analogWrite(M2, i);
		delay(160);
	}
	
	digitalWrite(M1A, !digitalRead(M1A));
	digitalWrite(M1B, !digitalRead(M1B));
	digitalWrite(M2A, !digitalRead(M2A));
	digitalWrite(M2B, !digitalRead(M2B));
	
}