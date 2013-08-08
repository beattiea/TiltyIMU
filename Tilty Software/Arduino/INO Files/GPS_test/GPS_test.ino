byte setUBXdataOn[] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF1, 0x00, 0x01, 0x00, 0x00}; // data to send to turn on UBX location protocol

void setup() {
	Serial.begin(115200);
	Serial3.begin(9600);
	while (!Serial) {}
	delay(5);
	Serial.println("begin...");
	
	calcChecksum(&setUBXdataOn[2], sizeof(setUBXdataOn) - 4);
	
	for (int i = 0; i < sizeof(setUBXdataOn); i++) {
		Serial.print(setUBXdataOn[i], HEX);
		Serial.print(", ");
		Serial3.write(setUBXdataOn[i]);
	}
	Serial.println();
}

void loop() {
	
	if (Serial.available()) {
		while (Serial.available())
		{	Serial3.write(Serial.read());}
	}
	
	if (Serial3.available()) {
		while (Serial3.available())
		{	Serial.print(char(Serial3.read()));}
	}
}

void calcChecksum(byte *checksumPayload, byte payloadSize) {
	byte CK_A = 0, CK_B = 0;
	for (int i = 0; i < payloadSize ;i++) {
		CK_A = CK_A + *checksumPayload;
		CK_B = CK_B + CK_A;
		checksumPayload++;
	}
	*checksumPayload = CK_A;
	checksumPayload++;
	*checksumPayload = CK_B;
}