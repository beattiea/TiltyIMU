#include <SatelliteRX.h>

SatelliteRX rx = SatelliteRX(Serial3);// Use Serial3 with RX pin 7. Must define a pin to be able to bind the receiver.

int aileron;

void setup() {
	Serial.begin(115200);
	
	rx.init(false); // boolean argument indicates whether receiver will attempt to bind at startup.
	rx.setAileron(&aileron);
}

void loop() {
	if (rx.readData()) {// readData returns true when a full set of data is actually read
	
		// Channels can be read by setting pointers to a user-defined variable
		Serial.print("Pointer: ");
		Serial.print(aileron);
		
		// Or channels can be read by directly reading the channel_data array in the receiver object
		// Channels can also be selected by using pre-defined indexes:
		// AILERON
		// RUDDER
		// THROTTLE
		// ELEVATOR
		// AUX1
		// AUX2
		// AUX3
		Serial.print("\t\t\tDirect: ");
		Serial.println(rx.channel_data[AILERON]);
		
		Serial.println();
	}
	
	delay(5);
}