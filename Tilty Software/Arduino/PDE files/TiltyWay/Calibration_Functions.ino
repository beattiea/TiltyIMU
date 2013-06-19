void calibrateSteeringRange() {
  int value;
  long timer1 = millis();
  while (millis() - timer1 < 3000) {
    value = analogRead(14);
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
    value = analogRead(14);
    if (value < steering_max) {
      timer1 = millis();
      steering_max = value;
    }
  }
  
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  
  settings.steeringMin = steering_min;
  settings.steeringMax = steering_max;
}
