#include <SatelliteRX.h>
#include <RCadapter.h>

#include <Wire.h>
#include "EEPROM.h"

#include <Servo.h>
//#include <FastServo.h>

RCadapter rx;

int servo_range = 500;
volatile int servo_value;

volatile bool request = false;

void setup() {
	pinMode(9, OUTPUT);
	rx.init();
	
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	
	rx.initServo(5);
	rx.initServo(6);
	rx.writeServo(6, -servo_range);
	delay(1000);
}

void loop() {
	if (rx.readSatRX() != NO_SAT_RX_CONNECTION) {
		rx.writeServo(5, rx.satRX.channel_data[THROTTLE] - 512);
	}
	
	rx.writeServo(6, servo_value);
	
	delay(2);
	digitalWrite(9, LOW);
	servo_value = (((rx.rxBuffer[0] & 0x03) << 8) | (rx.rxBuffer[1] & 0xFF)) - 512;
}

void requestEvent() {
	Wire.write(0x03 & rx.rxBuffer[0]);
	Wire.write(rx.rxBuffer[1]);
	/*
	byte buff[6];// = {rx.channel_data[AILERON], rx.channel_data[ELEVATOR], rx.channel_data[RUDDER], rx.channel_data[THROTTLE], \
		rx.channel_data[AUX1], rx.channel_data[AUX2]};
	for (int i = 0; i < 6; i++) {
		buff[i] = map(rx.satRX.channel_data[i], 0, 1024, 0, 255);
	}
	Wire.write(buff, 6);
	*/
}

void receiveEvent(int howMany) {
	rx.getData(howMany);
}