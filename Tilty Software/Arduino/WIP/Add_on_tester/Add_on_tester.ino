#include <i2c_t3.h>

#define BUFFER_SIZE 10

void setup() {
	Serial.begin(115200);
	Serial3.begin(57600);
	
	delay(20);
	
	Wire.begin(I2C_MASTER, 0, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
	
	delay(10);
}

uint8_t buf_index = 0;
byte buffer[BUFFER_SIZE];

void loop() {
	
	if (Serial.available()) {
		if (Serial.peek() == '.') {
			Serial.println("\nBeginTransmission...");
			Wire.beginTransmission(0x03);
			for (int i = 0; i < buf_index; i++) {
				Serial.print("I2C write: ");
				Serial.println(buffer[i]);
				Wire.write(buffer[i]);
			}
			Serial.read();
			buf_index = 0;
			Wire.endTransmission();
			Serial.println("End transmission.\n");
		}
		
		else if (Serial.peek() == '/') {
			buf_index = 0;
		}
		
		else {
			while (Serial.available()) {
				int val = parseInt();
				buffer[buf_index] = val;
				Serial.print("Buffer ");
				Serial.print(buf_index);
				Serial.print(": ");
				Serial.println(val);
				buf_index++;
			}
		}
	}
	
	while (Serial3.available()) {
		Serial.print(char(Serial3.read()));
	}
}


int parseInt() {
	int value = 0;
	while (Serial.available()) {
		int data = Serial.read() - 0x30;
		
		if (data < 0 || data > 9) {	return value;}
		else {	value = value * 10 + data;}
	}
	
	return value;
}