#include <SatelliteRX.h>

SatelliteRX rx = SatelliteRX(Serial3);// Use Serial3 with RX pin 7. Must define a pin to be able to bind the receiver.

int aileron;

void setup() {
	rx.init(false); // boolean argument indicates whether receiver will attempt to bind at startup.
	rx.setAileron(&aileron);
}

void loop() {
	rx.readData();
	
	
	// Channels can be read by setting pointers to a user-defined variable
	Serial.print("Pointer: ");
	Serial.println(aileron);
	
	// Or channels can be read by directly reading the channel_data array in the receiver object
	// Channels can also be selected by using pre-defined indexes:
	// AILERON
	// RUDDER
	// THROTTLE
	// ELEVATOR
	// AUX1
	// AUX2
	// AUX3
	Serial.print("Direct: ");
	Serial.println(rx.channel_data[AILERON]);
	
	Serial.println();
}