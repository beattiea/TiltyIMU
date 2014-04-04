#include <i2c_t3.h>

#define BUFFER_SIZE 32

void setup() {
	Serial.begin(115200);
	Serial3.begin(57600);
	
	delay(20);
	
	Wire.begin(I2C_MASTER, 0, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_200);
	
	delay(10);
}

uint8_t buf_index = 0;
byte buffer[BUFFER_SIZE];

void loop() {
	/*
	Wire.beginTransmission(0x03);
	Wire.write(4);
	Wire.write(0);
	Wire.write(0);
	Wire.write(0);
	Wire.write(0);
	Wire.endTransmission();
	delay(1);
	
	while (Serial) {
		Wire.beginTransmission(0x03);
		Wire.write(4);
		Wire.endTransmission();
		delayMicroseconds(1000);
		Wire.requestFrom(0x03, 4);
		getFloat();
		Serial.println();
		delay(100);
	}
	*/
	if (Serial.available()) {
		//long start = micros();
		if (Serial.peek() == '.') {	Serial.read(); sendBuffer();}
		
		else if (Serial.peek() == '/') {
			buf_index = 0;
			Serial.read();
		}
		
		else if (Serial.peek() == 'r') {	requestData();}
		
		else if (Serial.peek() - 0x30 >= 0 && Serial.peek() - 0x30 <= 9){
			int val = parseInt();
			buffer[buf_index] = val;
			Serial.print("Buffer ");
			Serial.print(buf_index);
			Serial.print(": ");
			Serial.print(val, HEX);
			Serial.print("\t(");
			Serial.print(val, DEC);
			Serial.println(")");
			buf_index++;
		}
		
		else if (Serial.peek() == 'd') {
			Serial.print("Time: ");
			long start = micros();
			Wire.requestFrom(0x03, 28);
			while (Wire.available() < 28) {}
			Serial.println(micros() - start);
			for (int i = 0; i < 28; i++) Serial.println(Wire.read());
			Serial.read();
		}
		
		else if (Serial.peek() == '{') {
			setI2Cpins1617();
			Serial.println("Set I2C line to pins 16 and 17 (5v bus)...\n");
			Serial.read();
		}
		else if (Serial.peek() == '}') {
			setI2Cpins1819();
			Serial.println("Set I2C line to pins 18 and 19 (3v3 bus)...\n");
			Serial.read();
		}
		
		else {	Serial.read();}
		
		//Serial.print("Time: ");
		//Serial.println(micros() - start);
	}
	
	while (Serial3.available()) {
		Serial.print(char(Serial3.read()));
	}
}


void sendBuffer() {
	Serial.println("\nBeginTransmission...");
	Wire.beginTransmission(0x03);
	for (int i = 0; i < buf_index; i++) {
		Serial.print("I2C write: ");
		Serial.println(buffer[i]);
		Wire.write(buffer[i]);
	}
	buf_index = 0;
	Wire.endTransmission();
	Serial.println("End transmission.\n");
}

void requestData() {
	Serial.read();
	if (buf_index != 0) {	sendBuffer();	delayMicroseconds(25);}
	if (Serial.available() <= 1) {
		int num;
		if (Serial.available()) {	num = parseInt();}
		else {	num = 1;}
		

		Wire.requestFrom(0x03, num);
		
		Serial.print("Requested ");
		Serial.print(num);
		Serial.println(" bytes from slave...");
		
		while (Wire.available() < num) {}
		if (num == 4) {
			get4Bytes();
		}
		else {
			for (int i = 0; i < num; i++) {
				Serial.print("Received value: 0x");
				char data = Wire.read();
				data < 0x10 ? Serial.print("0") : Serial.print(char(27));
				Serial.print(data, HEX);
				Serial.print("\t(");
				Serial.print(data, DEC);
				Serial.println(")");
			}
		}
		Serial.println();
	}
}

int parseInt() {
	int value = 0;
	while (Serial.available()) {
		int data = Serial.peek() - 0x30;
		
		if (data < 0 || data > 9) {	return value;}
		else {	
			Serial.read();
			value = value * 10 + data;
		}
	}
	
	return value;
}


void get4Bytes() {
	union int32_union {
		uint8_t bytes[4];
		int32_t int32;
		float flt;
	} int32_union;
	
	for (int i = 0; i < 4; i++) {
		int32_union.bytes[i] = Wire.read();
		Serial.print("Received value: ");
		Serial.print(int32_union.bytes[i], HEX);
		Serial.print("\t(");
		Serial.print(int32_union.bytes[i], DEC);
		Serial.println(")");
	}
	
	Serial.print("Parsed integer value: ");
	Serial.println(int32_union.int32);
	Serial.print("Parsed float value: ");
	Serial.println(int32_union.flt, 5);
}

void setI2Cpins1819()
{
    CORE_PIN18_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN19_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(16) = 0; // input
    CORE_PIN16_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(17) = 0; // input
    CORE_PIN17_CONFIG = PORT_PCR_MUX(1);
}

// Sets the I2C bus pins on the Teensy to 16 and 17
void setI2Cpins1617()
{
    CORE_PIN16_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN17_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(18) = 0; // input
    CORE_PIN18_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(19) = 0; // input
    CORE_PIN19_CONFIG = PORT_PCR_MUX(1);
}