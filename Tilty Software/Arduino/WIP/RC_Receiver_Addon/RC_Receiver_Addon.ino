#include <Wire.h>
#include <SatelliteRX.h>
#include <Servo.h>

SatelliteRX rx = SatelliteRX(Serial);
Servo myServo;

void setup() {
	// Initialize the I2C line at 400kHz
	TWBR = 400000L;
	Wire.begin(0x15);
	
	// Set up data Request and Receive handlers
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	
	// Initialize Spektrum Satellite receiver
	rx.init();
	
	// Initialize the servo
	myServo.attach(4);
}

void loop() {
	rx.readData();
	myServo.write(map(rx.channel_data[THROTTLE], 0, 1024, 0, 179));
}


void requestEvent() {
	
	byte buff[6];// = {rx.channel_data[AILERON], rx.channel_data[ELEVATOR], rx.channel_data[RUDDER], rx.channel_data[THROTTLE], \
		rx.channel_data[AUX1], rx.channel_data[AUX2]};
	for (int i = 0; i < 6; i++) {
		buff[i] = map(rx.channel_data[i], 0, 1024, 0, 255);
	}
	Wire.write(buff, 6);
}

void receiveEvent(int howMany) {
	// nothing to do yet
}
