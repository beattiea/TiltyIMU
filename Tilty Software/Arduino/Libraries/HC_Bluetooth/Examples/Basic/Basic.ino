#include <HC_Bluetooth.h>

HC_Bluetooth blue = HC_Bluetooth(Serial1, 15);

void setup() {
	//blue = HC_Bluetooth(printStuff);
	pinMode(13, OUTPUT);
	blue.begin(115200);
	delay(100);
	pinMode(15, OUTPUT);
	digitalWrite(15, LOW);
	//blue.commandMode();
	//Serial1.begin(115200);
	//pinMode(15, OUTPUT);
	//digitalWrite(15, HIGH);
}

char array[64] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\n', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\n', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

void loop() {
	/*
	if (blue.available()) {
		digitalWrite(13, HIGH);
		Serial.print("Sent: ");
		Serial.println(blue.available());//blue.available());
		while (blue.available()) {
			char data = blue.read();
			Serial.print(data);
			blue.print(data);
		}
		Serial.println();
	}
	digitalWrite(13, LOW);
	delay(1);
	*/
	
	if (Serial.available()) {
		Serial.read();
		digitalWrite(15, !digitalRead(15));
	}
	
	//Serial.println(blue.checkOK());
	//Serial.println();
	blue.checkOK();
	Serial.print("Function Read: ");
	Serial.println(digitalRead(15));
	delay(100);
}