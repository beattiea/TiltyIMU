#include "Servo.h"

byte inputs[4] = {9, 8, 5, 6};// Input pins
byte order[sizeof(inputs)];// Order of data input
unsigned long last_read = 0;// Time of last input reading

uint8_t index = 0;// channel to read index

unsigned long channel_start[sizeof(order)];
unsigned long channel_stop[sizeof(order)];

uint16_t channel_min[sizeof(order)];
uint16_t channel_max[sizeof(order)];
uint16_t channel_value[sizeof(order)];

Servo servo;
#define SERVO_PIN 4

void setup() {
	Serial.begin(115200);
	servo.attach(SERVO_PIN);
	
	/*
	while (true) {
		uint16_t count = TCNT1;
		delayMicroseconds(1);
		count = TCNT1 - count;
		Serial.println(count);
		delay(500);
	}
	*/
	
	
	syncStart(); // Finds gap between transmission of values
	getOrder(); // finds input order to determine channel number to input pin map
	index = 0;
}

void loop() {
	if (digitalRead(order[index])) {
		channel_start[index] = TCNT1;//micros();
		
		if (index != 0) {
			channel_stop[index - 1] = channel_start[index];
		}
		
		index++;
		
		if (index == sizeof(order)) {
			while (digitalRead(order[index - 1])) {}
			channel_stop[index - 1] = TCNT1;//micros();
			index = 0;
			
			for (int i = 0; i < sizeof(order); i++) {
				channel_value[i] = channel_stop[i] - channel_start[i];
				if (channel_value[i] < channel_min[i] || channel_min[i] == 0) { channel_min[i] = channel_value[i];}
				if (channel_value[i] > channel_max[i] || channel_max[i] == 0) { channel_max[i] = channel_value[i];}
				/*
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
				*/
			}
			if (channel_start[0] < channel_stop[0]) {
				servo.writeMicroseconds((channel_value[0] - channel_min[0]) / 2 + 1000);
			}
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