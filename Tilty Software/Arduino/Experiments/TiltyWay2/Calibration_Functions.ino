void calibrateSteeringRange() {
  int value;
  long timer1 = millis();
  while (millis() - timer1 < 3000) {
    value = analogRead(STEERING_SENSE);
    if (value < steering_min) {
      timer1 = millis();
      steering_min = value;
    }
  }
  
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  
  timer1 = millis();
  while (millis() - timer1 < 3000) {
    value = analogRead(STEERING_SENSE);
    if (value < steering_max) {
      timer1 = millis();
      steering_max = value;
    }
  }
  
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
}



void calibrateIMU() {//  Run this to see when IMU angle reading has settled
  getAngles();
  Serial.print("Pitch: ");
  Serial.print(pitch, 5);
  Serial.print("      dPitch: ");
  Serial.println(dPitch, 5);
}
