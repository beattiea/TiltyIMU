//#define Serial3 Serial3

int channel[6];

void setup() {
	delay(10);
	Serial.begin(115200);
	delay(10);
	Serial3.begin(115200);
	
	Serial3.clear();
	
	while (Serial3.read() != 0x03) {}
}

void loop() {
	if (Serial3.available() == 16) {
		//Serial3.read();
		//Serial3.read();
		for (int i = 0; i < 7; i++) {
			uint16_t data;
			data = Serial3.read() << 8;
			data |= Serial3.read();
			Serial.println(data, HEX);
			
			//int channel = data[0] & 0x7B;
			//int value = data[0] << 8 | data[1];
			//Serial.println(channel);
			//Serial.println(value);
		}
		Serial.println();
	}
	if (Serial.available()) {
		Serial.read();
		while (Serial3.available()) {
			Serial3.read();
		}
	}
	//delay(5);
}

bool readRx() {
	if (Serial3.available() >= 16) {
		Serial.println("READING FUCKING SERIAL DATA!");
		Serial3.read();
		delay(1);
		Serial3.read();
		delay(1);
		for (int i = 0; i < 6; i++) {
			int data = Serial3.read() << 8;
			Serial.println("Read byte 1");
			delay(1);
			data |= Serial3.read();
			Serial.println("Read byte 2");
			int ch_number = data & 0x7b00;
			channel[ch_number] = data & 0x03FF;
			Serial.println("Calculated data");
		}
		Serial3.clear();
		//printRx();
		return true;
	}
	else {
		Serial.print("Available: ");
		Serial.println(Serial3.available());
	}
	
	return false;
}

void printRx() {
	for (int i = 0; i < 6; i++) {
		Serial.print("Channel ");
		Serial.print(i + 1);
		Serial.print(": ");
		Serial.println(channel[i]);
	}
}