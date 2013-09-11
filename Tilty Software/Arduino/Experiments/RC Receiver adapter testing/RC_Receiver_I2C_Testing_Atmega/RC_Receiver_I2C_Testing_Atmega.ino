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

int channel;
volatile int counter = 0;
volatile int channels[5] = {100, 100, 100, 100, 100};

unsigned long even_start;
bool even_state = false;

unsigned long odd_start;
bool odd_state = false;


void setup()
{	
	//Serial.begin(9600);
	//delay(10);
	Wire.begin(2);				// join i2c bus with address #2
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent); // register event
	
	//attachInterrupt(2, evenRead, CHANGE);
	//attachInterrupt(3, oddRead, CHANGE);
}

void loop()
{
	/*
	if (micros() - even_start > 7500 || micros() - odd_start > 7500) {
		synced = true;
		counter = 0;
	}
	*/
	/*
	Serial.print("Channel: ");
	Serial.print(channel);
	Serial.println();
	*/
	Serial.println("Running...");
	delay(1000);
	
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
	int val = 1000;
	//Wire.write(val >> 8);
	//Wire.write(val & 0xFF);
	//Wire.write(channels[channel] & 0xFF00);
	//Wire.write(channels[channel] & 0xFF);
	//Wire.write(map(channels[0], 0, 1024, 0, 255));
}

void receiveEvent(int number) {
	int x = Wire.read();
	Serial.println(x);
}

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