char buffer[256];

// Takes a float variable, converts it to a 4 byte array, and sends it out over bluetooth
void sendHeading(float buffer) {
	union var_types {
		float f;
		char c[4];
	} var_types;
	
	var_types.f = buffer;
	Serial1.write(var_types.c);
}


// reads four bytes from bluetooth, converts them into a float, and returns that value
float receiveHeading() {
	union var_types {
		float f;
		char c[4];
	} var_types;
	
	for (int i = 0; i < 4; i++) {
		var_types.c[i] = Serial1.read();
	}
	
	return var_types.f;
}


// Takes a string representing the slave Address. Ex: "98D3,31,B0339B"
int connectToSlave(char* address) {
	digitalWrite(bt_cmd, HIGH);
	Serial1.print("AT\r\n");
	Serial1.flush();

	int result = parseCommandResponse();
	if (result == 1) {
		Serial.println("Got OK");
		
		Serial1.print("AT+LINK=");
		Serial1.print(address);
		Serial1.print("\r\n");
		Serial1.flush();
		digitalWrite(bt_cmd, LOW);
		//result = pareCommandResponse();
		while (!Serial1.available()) {}
		while (Serial1.available()) {
			Serial.print((char)Serial1.read());
		}
	}
	else {	Serial.println("Didn't get OK");}
}


// Reads data into a buffer and checks to see if the command response is as expected
// This is far from done
int parseCommandResponse() {
	int i = 0;
    while (Serial1.available()) {
		buffer[i] = Serial1.read();
		i++;
	}
	
	int ok = checkOK();
	if (ok == 1) {	return 1;}
	if (ok == 0 || ok == 2) {	return 0;}
}


// Checks if command response contains or is OK
int checkOK() {
	int i = 0;
	while ((buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '\r' || buffer[i] == '\n') {
		if (buffer[i] == 'O' && buffer[i+1] == 'K' && buffer[i+2] == '\r' && buffer[i+3] == '\n') {	return 1;}
		else if (buffer[i] == 'F' && buffer[i+1] == 'A' && buffer[i+2] == 'I' && buffer[i+3] == 'L' && buffer[i+4] == '\r' && buffer[i+5] == '\n') {	return 2;}
		i++;
	}
	return 0;
}


// Used for testing bluetooth functions
void testBT() {
	connectToSlave(board2);
}


#define OK 1


#define STATE "+STATE:" // Always starts a state command response
#define INITIALIZED "INITIALIZED"
#define READY "READY"
#define PAIRABLE "PAIRABLE"
#define PAIRED "PAIRED"
#define INQUIRING "INQUIRING"
#define CONNECTING "CONNECTING"
#define CONNECTED "CONNECTED"
#define DISCONNECTED "DISCONNECTED"
#define UNKNOWN "UNKNOWN"

// Bluetooth disconnect responses
#define DISC "+DISC:" // Always starts a disconnect command response
#define SUCCESS "SUCCESS"
#define LINK_LOSS "LINK_LOSS"
#define NO_SLC "NO_SLC"
#define TIMEOUT "TIMEOUT"
#define ERROR "ERROR"
