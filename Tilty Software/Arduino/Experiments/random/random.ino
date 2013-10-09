#include <SatelliteRX.h>
#include <RCadapter.h>

#include <Wire.h>
#include "EEPROM.h"

#include <Servo.h>
//#include <FastServo.h>

byte inputs[3] = {2, 3, 4};

RCadapter rx = RCadapter();

void setup() {
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
	
	
}

void loop() {
	if (rx.readRCinputs()) {
		for (int i = 0; i < 3; i++) {
			Serial.print("Channel: ");
			Serial.println(rx.channel_values[i]);
		}
		Serial.println();
	}
}