void printYPR() {
	Serial.print("Yaw: ");
	Serial.print(ypr[YAW]);
	Serial.print("\t\tPitch: ");
	Serial.print(ypr[PITCH]);
	Serial.print("\t\tRoll: ");
	Serial.print(ypr[ROLL]);
	Serial.println();
}