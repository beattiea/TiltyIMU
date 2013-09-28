#include <SatelliteRX.h>
#include <RCadapter.h>

#include <Wire.h>
#include "EEPROM.h"

#include <Servo.h>
//#include <FastServo.h>

RCadapter rx;

int servo_range = 500;

void setup() {
	
	Wire.begin(0x02);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	
	rx.initServo(6);
	rx.writeServo(6, -servo_range);
	delay(1000);
}

void loop() {
	
	for (int i = -servo_range; i < servo_range; i++) {
		rx.writeServo(6, i);
		delay(2);
	}
	
	for (int i = servo_range; i > -servo_range; i--) {
		rx.writeServo(6, i);
		delay(2);
	}
	
}

void requestEvent() {
	
	byte buff[6];// = {rx.channel_data[AILERON], rx.channel_data[ELEVATOR], rx.channel_data[RUDDER], rx.channel_data[THROTTLE], \
		rx.channel_data[AUX1], rx.channel_data[AUX2]};
	for (int i = 0; i < 6; i++) {
		buff[i] = map(rx.satRX.channel_data[i], 0, 1024, 0, 255);
	}
	Wire.write(buff, 6);
}

void receiveEvent(int howMany) {
	// nothing to do yet
}