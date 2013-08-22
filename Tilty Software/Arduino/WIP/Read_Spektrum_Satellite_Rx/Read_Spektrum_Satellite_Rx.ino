#define rx_port Serial2

int channel[6];

void setup() {
	rx_port.begin(115200);
}

void loop() {
	if (readRx()) printRx();
}

bool readRx() {
	if (rx_port.available() == 16) {
		rx_port.read();
		rx_port.read();
		for (int i = 0; i < 7; i++) {
			int data = rx_port.read() << 8 | rx_port.read();
			int ch_number = data & 0x7b00;
			channel[ch_number] = data & 0x03FF;
		}
	
		return true;
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