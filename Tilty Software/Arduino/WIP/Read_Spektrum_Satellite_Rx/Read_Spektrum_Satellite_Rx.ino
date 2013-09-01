//#define Serial3 Serial3

int channel[6];

void setup() {
	Serial.begin(115200);
	
	//startBind();
	
	//while (!Serial) {}
	
	pinMode(7, INPUT);
	
	//delay(10);
	
	Serial3.begin(115200);
}

void loop() {
	/*
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
	*/
	if (Serial3.available()) {
		if (Serial3.read() == 0x03) {
			byte data[14];
			Serial.println("\tNew Data");
			while (Serial3.available() < 15) {
				delayMicroseconds(100);
			}
			Serial.print("0x");
			Serial.println(Serial3.read(), HEX);
			for (int i = 0; i < 14; i++) {
				data[i] = Serial3.read();
			}
			/*
			for (int i = 0; i < 13; i += 2) {
				Serial.print("Data: 0x");
				Serial.print(data[i], HEX);
				Serial.print(" + 0x");
				Serial.println(data[i + 1], HEX);
			}
			Serial.println();
			*/
			
			for (int i = 0; i < 13; i += 2) {
				int value = data[i] << 8 | data[i + 1];
				channel[i] = value >> 10;
				value = value & 0b000001111111111;
				
				Serial.print("Channel: ");
				Serial.print(channel[i]);
				Serial.print(" = ");
				Serial.println(value);
			}
			Serial.println();
			
			/*
			for (int i = 0; i < 7; i++) {
				int value;
				channel[i] |= (data[i] & 0b11111000) >> 3;
				value |= (data[i] << 8) | data[i * 2 - 1];
				Serial.print("Channel: ");
				Serial.print(channel[i]);
				Serial.print(" = ");
				Serial.println(value, HEX);
			}
			*/
		}
	}
	//delay(5);
}

void startBind() {
	pinMode(7, OUTPUT);
	
	digitalWrite(7, HIGH);
	delay(100);
	
	for (int i = 0; i < 4; i++) {
		digitalWrite(7, !digitalReadFast(7));
		delayMicroseconds(120);
		
		digitalWrite(7, !digitalReadFast(7));
		delayMicroseconds(120); 
	}
}