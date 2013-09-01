#include <SatelliteRX.h>

SatelliteRX rx = SatelliteRX(Serial3);// Use Serial3 with RX pin 7. Must define a pin to be able to bind the receiver.

void setup() {
	rx.init();
}

void loop() {
	rx.readData();
	
	
	for (int i = 0; i < 7; i++) {
		Serial.print("Channel ");
		Serial.print(i);
		Serial.print(": ");
		Serial.print(rx.channel_data[i]);
		
		Serial.println();
	}
	Serial.println();
	
	//delay(10);
}