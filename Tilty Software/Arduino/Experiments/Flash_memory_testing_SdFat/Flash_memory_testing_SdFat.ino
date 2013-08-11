#include <SPI.h>
#include <SdSpi.h>

#define ss 10

SdSpi flash;

void setup() {
	Serial.begin(115200);
	
	pinMode(ss, OUTPUT);
	digitalWrite(ss, HIGH);
	
	while (!Serial) {}
	
	flash.begin();
	flash.init(2);
}

byte buffer[4096];

void loop() {
	enableWrite();
	
	long start = micros();
	
	for (int n = 0; n < 16; n++) {
		digitalWrite(ss, LOW);
		flash.send(0x02);
		flash.send(0x00);
		flash.send(n);
		flash.send(0x00);
		for (int i = 0; i < 256; i++) {
			flash.send(i);
		}
		digitalWrite(ss, HIGH);
		while (!checkReady()) { }//delayMicroseconds(1);}
		enableWrite();
	}
	
	long stop = micros();
	
	for (int n = 0; n < 16; n++) {
		digitalWrite(ss, LOW);
		flash.send(0x03);
		flash.send(0x00);
		flash.send(n);
		flash.send(0x00);
		for (int i = 0; i < 256; i++) {
			buffer[(256 * n) + i] = flash.receive();
			//flash.receive(&buffer[0], 4096);
		}
		digitalWrite(ss, HIGH);
	}
	
	long stop2 = micros();
	
	eraseSector(0);
	
	long stop3 = micros();
	
	for (int i = 0; i < sizeof(buffer); i++) {
		Serial.print("Loaded value from ");
		Serial.print(i);
		Serial.print(":\t");
		Serial.println(buffer[i]);
	}
	
	
	Serial.print("Time to write 4kB (s): ");
	Serial.println((stop - start) / 1000000.0, 5);
	Serial.print("Time to read 4kB (s): ");
	Serial.println((stop2 - stop) / 1000000.0, 5);
	Serial.print("Time to erase a sector (s): ");
	Serial.println((stop3 - stop2) / 1000000.0, 5);
	
	while (!Serial.available()) {}
	Serial.read();
	
	for (int n = 0; n < 16; n++) {
		digitalWrite(ss, LOW);
		flash.send(0x03);
		flash.send(0x00);
		flash.send(n);
		flash.send(0x00);
		for (int i = 0; i < 256; i++) {
			buffer[(256 * n) + i] = flash.receive();
		}
		digitalWrite(ss, HIGH);
	}
	
	for (int i = 0; i < sizeof(buffer); i++) {
		Serial.print("Loaded value from ");
		Serial.print(i);
		Serial.print(":\t");
		Serial.println(buffer[i]);
	}
	
	while (!Serial.available()) {}
	Serial.read();
}

void enableWrite() {
	digitalWrite(ss, LOW);
	flash.send(0x06);
	digitalWrite(ss, HIGH);
	while(!checkReady) {}//delayMicroseconds(1);}
}

bool checkReady() {
	digitalWrite(ss, LOW);
	flash.send(0x05);
	byte status = flash.receive();
	digitalWrite(ss, HIGH);
	
	if (status & 0x01) {	return false;}
	else {	return true;}
}

void eraseSector(int _addr) {
	Serial.println("Erasing sector…");
	digitalWrite(ss, LOW);
	flash.send(0x20);
	flash.send(_addr >> 16);
	flash.send(_addr >> 8);
	flash.send(_addr);
	digitalWrite(ss, HIGH);
	while (!checkReady()) {}//delayMicroseconds(1);}
}