// Error codes
// 0 = IMU not detected or failed initialization (flashes "SOS": ...---...).
// 1 = initial IMU DMP memory load failed.
// 2 = DMP configuration updates failed.
// 3 = IMU FIFO overflow error. Code is too inefficient and IMU is not being read frequently enough.
// 4 = Maximum pitch or roll exceeded.
// 5 = Maximum power/speed exceeded.
// 6 = User reset.
void SOS(int error, char* details) {
	motors.setMotors(0, 0);
	
	tiltPID.reset();
	tilt_power = 0;
	
	pinMode(LED, OUTPUT);
	
	//while (!digitalRead(RESET_PIN)) {
	while (abs(pitch) >= MAX_PITCH || abs(roll) >= MAX_ROLL) {
		if (Serial) {
			Serial.print("error code: ");
			Serial.print(error);
			Serial.println(details);
		}
		
		if (error) {
			for (int i = 0; i < error; i++) {
				digitalWrite(LED, HIGH);
				delay(250);
				digitalWrite(LED, LOW);
				delay(250);
			}
		}
		else {
			// S
			for (int i = 0; i < 3; i++) {
				digitalWrite(LED, HIGH);
				delay(250);
				digitalWrite(LED, LOW);
				delay(250);
			}
			// O
			for (int i = 0; i < 3; i++) {
				digitalWrite(LED, HIGH);
				delay(500);
				digitalWrite(LED, LOW);
				delay(500);
			}
			// S
			for (int i = 0; i < 3; i++) {
				digitalWrite(LED, HIGH);
				delay(250);
				digitalWrite(LED, LOW);
				delay(250);
			}
		}
		
		if (Serial.available()) {
			if (Serial.read() == 'r') {	break;}
		}
		delay(1000);
	}
	digitalWrite(LED, LOW);
	
	checkToStart();
}



void printYPR() {
	Serial.print("Yaw: ");
	Serial.print(yaw);
	Serial.print("\t\tPitch: ");
	Serial.print(pitch);
	Serial.print("\t\tRoll: ");
	Serial.print(roll);
	Serial.println();
}

void printPID() {
	Serial.print("P: ");
	Serial.print(tiltPID.Pvalue);
	Serial.print("\t\tI: ");
	Serial.print(tiltPID.Ivalue);
	Serial.print("\t\tD: ");
	Serial.print(tiltPID.Dvalue);
	Serial.print("\t\tPID: ");
	Serial.print(tilt_power);
	Serial.println();
}


long time;
bool print = false;
void testIMU() {
	float ypr2[3];
	
	//if (readDMP()) {
		//Serial.print("MPU DMP\t\t");
		//printYPR();
		
		//fIMU.getYawPitchRoll(ypr2);

		if (print) {
			Serial.print(ypr[PITCH]);
			Serial.print(", ");
			Serial.print(ypr[ROLL]);
		
			Serial.print(", ");
			Serial.print(ypr2[PITCH]);
			Serial.print(", ");
			Serial.print(ypr2[ROLL]);
		
			Serial.print(", ");
			Serial.print(ypr[PITCH] - ypr2[PITCH]);
			Serial.print(", ");
			Serial.print(ypr[ROLL] - ypr2[ROLL]);
		
			Serial.print(", ");
			Serial.print(millis() - time);
			time = millis();
		
			Serial.println();
		}
	//}
	if (Serial.available()) {	Serial.read(); print = !print;}
}
