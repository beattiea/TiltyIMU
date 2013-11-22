void servoWrite(Servo servo, int value) {
	servo.writeMicroseconds(map(value, -MAX_PID, MAX_PID, 1500 - SERVO_RANGE, 1500 + SERVO_RANGE));
}

void setServos() {
	servoWrite(servo1, tilt_power);
	servoWrite(servo2, 0);
}