const int CENTER_SERVO_VALUE = 1500;

void writeServos(int go_val, int turn_val) {
	go_servo.writeMicroseconds(go_val + CENTER_SERVO_VALUE);
	turn_servo.writeMicroseconds(turn_val + CENTER_SERVO_VALUE);
}