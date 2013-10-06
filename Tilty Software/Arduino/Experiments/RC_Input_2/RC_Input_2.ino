#include "Servo.h"

byte inputs[6] = {13, 12, 11, 10, 9, 8};// Input pins
byte order[sizeof(inputs)];// Order of data input
unsigned long last_read = 0;// Time of last input reading

uint8_t index = 0;// channel to read index

unsigned long channel_start[sizeof(order)];
unsigned long channel_stop[sizeof(order)];

uint16_t channel_min[sizeof(order)];
uint16_t channel_max[sizeof(order)];
uint16_t channel_value[sizeof(order)];

Servo servo;

void setup() {
	Serial.begin(115200);
	
	syncStart(); // Finds gap between transmission of values
	getOrder(); // finds input order to determine channel number to input pin map
	index = 0;
	servo.attach(2);
}

void loop() {
	if (digitalRead(order[index])) {
		channel_start[index] = micros();
		
		if (index != 0) {
			channel_stop[index - 1] = channel_start[index];
		}
		
		index++;
		
		if (index == sizeof(order)) {
			while (digitalRead(order[index - 1])) {}
			channel_stop[index - 1] = micros();
			index = 0;
			
			for (int i = 0; i < sizeof(order); i++) {
				channel_value[i] = channel_stop[i] - channel_start[i];
				if (channel_value[i] < channel_min[i] || channel_min[i] == 0) { channel_min[i] = channel_value[i];}
				//if (channel_value[i] > channel_max[i] || channel_max[i] == 0) { channel_max[i] = channel_value[i];}
				if (!Serial.available()) {
					Serial.print("Channel ");
					Serial.print(i + 1);
					Serial.print(": ");
					
					Serial.print(channel_value[i] - channel_min[i]);
					Serial.print("\t\t");
					Serial.print(channel_stop[i] - channel_start[i]);
					Serial.print("\t\t");
					Serial.println(channel_min[i]);
				}
				
				if (Serial.available()) {
					Serial.print(channel_value[i] - channel_min[i]);
					Serial.print(", ");
				}
			}
			servo.writeMicroseconds(channel_value[5] - channel_min[5] + 1080);
			Serial.println();
		}
	}
}



void syncStart() {
	while (last_read == 0 || micros() - last_read < 10000)
	{
		for (int i = 0; i < sizeof(inputs); i++) {
			if (digitalRead(inputs[i])) {
				last_read = micros();
			}
		}
	}
	Serial.println("Found start point...");
}



void getOrder() {
	while (index < sizeof(order) && micros()) {
		for (int i = 0; i < sizeof(inputs); i++) {
			if (!inOrder(inputs[i])) {// Only reads an input pin if it hasn't already been read
				if (digitalRead(inputs[i])) {
					last_read = micros();
					order[index] = inputs[i];
					Serial.print("Read ");
					Serial.println(order[index]);
					index++;
				}
			}
		}
	}
	Serial.print("Found input order: ");
	for (int i = 0; i < sizeof(order) - 1; i++) {
		Serial.print(order[i]);
		Serial.print(", ");
	}
	Serial.println(order[sizeof(order) - 1]);
}



bool inOrder(uint8_t num) {
	for (int i = 0; i < sizeof(order); i++) {
		if (order[i] == num) { return true;}
	}
	return false;
}