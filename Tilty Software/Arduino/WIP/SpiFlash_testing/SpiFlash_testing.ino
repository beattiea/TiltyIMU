
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
	//flash.eraseSector(0);
}

void loop() {
	Serial.println(flash.write(3.14159, 2048));
	Serial.println(flash.readFloat(2048), 5);
	//flash.eraseSector(0);
	//flash.write(314159, 0x00);
	//Serial.println(flash.readInt(0x00));
	
	// Read a given length to a given buffer
	//byte buffer[256];
	//flash.read(&buffer[0], 0, sizeof(buffer));
	
	while (!Serial.available()) {}
	Serial.read();
}