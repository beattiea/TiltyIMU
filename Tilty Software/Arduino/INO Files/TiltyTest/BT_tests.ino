bool checkBTok() {
	elapsedMillis timer;
	char ok[4] = {'O', 'K', '\r', '\n'};
	
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT\r\n");
	delayMicroseconds(25);
	
	//digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);
	
	while (Serial1.available() < sizeof(ok) && timer < 250) {}
	for (int i = 0; i < sizeof(ok); i++) {
		if (Serial1.read() != ok[i]) {	return false;}
	}
	return true;
}

bool getBTversion() {
	elapsedMillis timer;
	char version[9] = {'+', 'V', 'E', 'R', 'S', 'I', 'O', 'N', ':'};
	
	Serial1.begin(BT_DEFAULT_BAUD);
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT+VERSION?\r\n");
	delayMicroseconds(25);
	
	//digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);
	
	while (Serial1.available() < sizeof(version) && timer < 250) {}

	while (Serial1.available()) {
		for (int i = 0; i < 9; i++) {
			Serial1.read();
		}
		while (Serial1.available()) {
			char data = Serial1.read();
			if (data != 'O' && data != 'K' && data != '\n' && data != '\r') {	Serial.print(data);}
			delay(1);
		}
	}
	Serial.println();
}

bool setBTbaud() {
	elapsedMillis timer;
	char ok[4] = {'O', 'K', '\r', '\n'};
	
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(50);
	
	Serial1.print("AT+UART=");
	Serial1.print(TILTY_DEFAULT_BT_BAUD);
	Serial1.print(",0,0\r\n");
	delayMicroseconds(50);

        while (Serial1.available() < sizeof(ok) && timer < 250) {}
	for (int i = 0; i < sizeof(ok); i++) {
		if (Serial1.read() != ok[i]) {	return false;}
	}
	
	//digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(50);
	
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT+RESET\r\n");
	delayMicroseconds(25);
	
	digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);
	
	Serial1.end();
	delay(25);
	Serial1.begin(TILTY_DEFAULT_BT_BAUD);
	delay(1000);
	
	int baud = findBaud();
	if (baud == 115200) {	return true;}
	else {	return false;}
}

bool setBTname() {
	elapsedMillis timer;
	
	digitalWrite(BT_COMMAND, HIGH);
	delay(10);
	
	Serial1.print("AT+NAME=TiltyBT\r\n");
	delay(25);
	
	//digitalWrite(BT_COMMAND, LOW);
	delay(10);

	delay(25);
	if (Serial1.available()) {
		while (Serial1.available()) {
			Serial.print((char)Serial1.read());
		}
	}
	else {	Serial.println();}
}


int _bauds[] = {9600, 38400, 57600, 115200, 230400, 460800};
int findBaud()
{
  for (int i = 0; i < sizeof(_bauds) / 4; i++)
  {
	digitalWrite(BT_COMMAND, HIGH);
	Serial1.begin(_bauds[i]);
	delay(100);
	Serial1.write("AT\r\n");
	delay(100);
	//digitalWrite(BT_COMMAND, LOW);

	if (Serial1.available()) 
	{
	  while (Serial1.available())//	 Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
	  {	Serial1.read();}
	  return _bauds[i];//  return the correct baud rate
	}
	Serial1.end();
        digitalWrite(BT_COMMAND, LOW);
  }
  return -1;
}
