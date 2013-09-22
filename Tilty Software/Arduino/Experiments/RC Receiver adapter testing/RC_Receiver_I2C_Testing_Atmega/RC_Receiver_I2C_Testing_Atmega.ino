// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

//#define TWI_FREQ 400000L

#include <Wire.h>

bool synced = false;

//int channel;
volatile int counter = 0;
volatile int channels[5] = {100, 100, 100, 100, 100};

unsigned long even_start;
bool even_state = false;

unsigned long odd_start;
bool odd_state = false;

int channel[6];

void setup()
{	
	//Serial.begin(9600);
	//delay(10);
	Wire.begin(2);				// join i2c bus with address #2
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent); // register event
        Serial.begin(115200);
	
	//attachInterrupt(2, evenRead, CHANGE);
	//attachInterrupt(3, oddRead, CHANGE);
}

void loop()
{
	if (Serial.available()) {
		if (Serial.read() == 0x03) {
			byte data[14];
			while (Serial.available() < 15) {
}
			for (int i = 0; i < 14; i++) {
				data[i] = Serial.read();
			}
			
			for (int i = 0; i < 13; i += 2) {
				int value = data[i] << 8 | data[i + 1];
				//channel[i] = value >> 10;
				value = value & 0b000001111111111;
                                channel[i] = value;
			}
		}
	}
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
	Wire.write(map(channel[3], 0, 1024, 0, 255));
	//Wire.write(val & 0xFF);
	//Wire.write(channels[channel] & 0xFF00);
	//Wire.write(channels[channel] & 0xFF);
	//Wire.write(map(channels[0], 0, 1024, 0, 255));
}

void receiveEvent(int number) {
	int x = Wire.read();
}
/*
void evenRead() {
	//if (synced) {
	channels[0] = 1000;
		if (!even_state) {  even_start = micros();}
		else {
				odd_start = micros();
				channels[counter] = even_start - odd_start;
				counter++;
			}
	//}
	even_state = !even_state;
}

void oddRead() {
	//if (synced) {
	channels[0] = 500;
		if (!odd_state) {  odd_start = micros();}
		else {
				even_start = micros();
				channels[counter] = even_start - odd_start;
				counter++;
			}
	//}
	odd_state = !odd_state;
}
*/
