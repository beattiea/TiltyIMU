
#include <SPI.h>
#include <SpiFlash.h>

#define ss 10

SpiFlash flash;

void setup() {
	Serial.begin(115200);
	
	pinMode(ss, OUTPUT);
	digitalWrite(ss, HIGH);
	
	while (!Serial) {}
	
	Serial.println("Begin...");
	
	flash.begin(10, 2);// start SPI flash instance witch slave select on pin 10 and clock divider of 2
	flash.eraseChip();
}

void loop() {
	Serial.println("Buffer data");
	int x = 0;
	
	long start = micros();
	
	for (int i = 0; i < 65536; i++) {
		flash.bufferData(i);
	}
	//flash.writeBuffer(x);
	
	long stop = micros();
	
	Serial.println(stop - start);
	
	// Read a given length to a given buffer
	//byte buffer[256 * sizeof(int)];
	//flash.read(&buffer[0], 0, sizeof(buffer));
	
	/*
	Serial.println("Loaded buffer data:");
	for (int i = 0; i < sizeof(buffer); i++) {
		Serial.println(buffer[i], BIN);
	}
	*/
	
	for (int i = 0; i < 65536; i++) {
		Serial.println(flash.readInt(i * sizeof(int)));
	}
	
	while (!Serial.available()) {}
	Serial.read();
}