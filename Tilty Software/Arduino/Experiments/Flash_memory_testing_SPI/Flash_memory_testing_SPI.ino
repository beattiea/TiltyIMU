#include <SPI.h>

#define ss 10

void setup() {
	Serial.begin(115200);
	
	pinMode(ss, OUTPUT);
	digitalWrite(ss, HIGH);
	
	while (!Serial) {}
	
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	
	SPI.begin();
	
	writeEnable();
	
	eraseChip();
	
	writeEnable();
	
}

byte buffer[4096];

void loop() {
	long start = micros();
	for (int n = 0; n < 16; n++) {
		digitalWrite(ss, LOW);
		SPI.transfer(0x02);
		SPI.transfer(0x00);
		SPI.transfer(n);
		SPI.transfer(0x00);
		for (int i = 0; i < 256; i++) {
			SPI.transfer(i);
		}
		digitalWrite(ss, HIGH);
		while (writeProgress()) { delayMicroseconds(5);}
		writeEnable();
	}
	
	long stop = micros();
	
	for (int n = 0; n < 16; n++) {
		digitalWrite(ss, LOW);
		SPI.transfer(0x03);
		SPI.transfer(0x00);
		SPI.transfer(n);
		SPI.transfer(0x00);
		for (int i = 0; i < 256; i++) {
			buffer[(256 * n) + i] = SPI.transfer(0);
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
	Serial.print("Time to read 4kB (us): ");
	Serial.println((stop2 - stop) / 1000000.0, 5);
	Serial.print("Time to read 4kB (us): ");
	Serial.println((stop3 - stop2) / 1000000.0, 5);
	
	while(!Serial.available()) {}
	Serial.read();
	
	for (int n = 0; n < 16; n++) {
		digitalWrite(ss, LOW);
		SPI.transfer(0x03);
		SPI.transfer(0x00);
		SPI.transfer(n);
		SPI.transfer(0x00);
		for (int i = 0; i < 256; i++) {
			buffer[(256 * n) + i] = SPI.transfer(0);
		}
		digitalWrite(ss, HIGH);
	}
	for (int i = 0; i < sizeof(buffer); i++) {
		Serial.print("Loaded value from ");
		Serial.print(i);
		Serial.print(":\t");
		Serial.println(buffer[i]);
	}
}

void writeEnable() {
	Serial.println("Enabling write...");
	digitalWrite(ss, LOW);
	SPI.transfer(0x06);
	digitalWrite(ss, HIGH);
	while (writeProgress()) {	delayMicroseconds(5);}
}

void eraseChip() {
	Serial.println("Erasing chip…");
	digitalWrite(ss, LOW);
	SPI.transfer(0xC7);
	digitalWrite(ss, HIGH);
	while (writeProgress()) {	delayMicroseconds(5);}
}

void eraseSector(int _addr) {
	Serial.println("Erasing chip…");
	digitalWrite(ss, LOW);
	SPI.transfer(0x20);
	SPI.transfer(_addr >> 16);
	SPI.transfer(_addr >> 8);
	SPI.transfer(_addr);
	digitalWrite(ss, HIGH);
	while (writeProgress()) {	delayMicroseconds(5);}
}

bool writeProgress() {
	digitalWrite(ss, LOW);
	SPI.transfer(0x05);
	byte status = SPI.transfer(0);
	digitalWrite(ss, HIGH);
	
	if (status & 0x01) {	return true;}
	else {	return false;}
}