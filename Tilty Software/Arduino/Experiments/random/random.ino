void setup() {
	Serial1.begin(115200);
	Serial3.begin(115200);
	pinMode(13, OUTPUT);
}

void loop() {
	//Serial3.println("Hello!");
	delay(100);
	//serialEvent1();
}

void serialEvent() {
	digitalWrite(13, HIGH);
	while (Serial.available()) {
		Serial3.print(char(Serial.read()));
	}
}

void serialEvent1() {
	Serial.print("Serial1: ");
	while (Serial1.available()) {
		Serial.print(char(Serial1.read()));
		delay(5);
	}
	//Serial.println("Wuddup");
	//digitalWrite(13, !digitalRead(13));
}