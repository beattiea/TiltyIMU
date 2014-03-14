const int MIN_VALUE = -750;
const int MAX_VALUE = 750;

void updatePID() {
	P = constrain(kP * ypr[PITCH], MIN_VALUE, MAX_VALUE);
	D = constrain(kD * (old_ypr[PITCH] - ypr[PITCH]), MIN_VALUE - P, MAX_VALUE - P);
	I = constrain(I + (kI * ypr[PITCH]), MIN_VALUE - P - D, MAX_VALUE - P - D);	// Calculate I and constrain it so that it does not exceed the max servo value when added to P and Dvalues
	
	S = -(analogRead(STEER_SENSE) - STEER_CENTER);
}

void resetPID() {
	P = 0;
	I = 0;
	D = 0;
	
	S = 0;
}