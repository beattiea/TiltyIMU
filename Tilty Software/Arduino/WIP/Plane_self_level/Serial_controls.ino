void setP() {
	delay(200);
	if (myPort.available()) {
		char data = myPort.read();
		if (data == 'p') {
			pitch_pid.kP = myPort.parseFloat();
		}
		else if (data == 'r') {
			roll_pid.kP = myPort.parseFloat();
		}
	}
}

void setI() {
	delay(200);
	if (myPort.available()) {
		char data = myPort.read();
		if (data == 'p') {
			pitch_pid.kI = myPort.parseFloat();
		}
		else if (data == 'r') {
			roll_pid.kI = myPort.parseFloat();
		}
	}
}

void setD() {
	delay(200);
	if (myPort.available()) {
		char data = myPort.read();
		if (data == 'p') {
			pitch_pid.kD = myPort.parseFloat();
		}
		else if (data == 'r') {
			roll_pid.kD = myPort.parseFloat();
		}
	}
}