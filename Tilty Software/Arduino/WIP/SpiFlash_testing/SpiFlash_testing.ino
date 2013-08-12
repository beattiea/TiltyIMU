
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
	flash.eraseSector(0);
}

void loop() {
	Serial.println("Buffer data");
	int x = 0;
	for (int i = 0; i < 256; i++) {
		if (i % 64 == 0 && i > 0) {
			Serial.println(i);
			Serial.print("\t\t\t\t\tWrite data results: ");
			Serial.println(flash.writeBuffer(x));
			x += 256;
		}
		flash.bufferData(i);
	}
	flash.writeBuffer(x);
	//Serial.println(flash.write(3.14159, 2048));
	//Serial.println(flash.readFloat(2048), 5);
	//flash.eraseSector(0);
	//flash.write(314159, 0x00);
	//Serial.println(flash.readInt(0x00));
	
	// Read a given length to a given buffer
	byte buffer[256 * sizeof(int)];
	//flash.read(&buffer[0], 0, sizeof(buffer));
	
	/*
	Serial.println("Loaded buffer data:");
	for (int i = 0; i < sizeof(buffer); i++) {
		Serial.println(buffer[i], BIN);
	}
	*/
	
	for (int i = 0; i < sizeof(buffer) / sizeof(int); i++) {
		Serial.println(flash.readInt(i * sizeof(int)));
	}
	
	while (!Serial.available()) {}
	Serial.read();
}