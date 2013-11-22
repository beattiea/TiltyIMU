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
  
  settings.steeringMin = steering_min;
  settings.steeringMax = steering_max;
}



void calibrateIMU() {//  Run this to see when IMU angle reading has settled
  getAngles();
  Serial.print("Pitch: ");
  Serial.print(pitch, 5);
  Serial.print("      dPitch: ");
  Serial.println(dPitch, 5);
}







void steeringCheck() {
  int ts;
  
  ts = analogRead(STEERING_SENSE);
  
  //myPort.println(ts);
  
  if (ts > settings.steeringMax + 2) {
    settings.steeringMax = ts;
    settings.steeringMin = ts - 180;
    
    /*
    myPort.print("New max steering set: Max = ");
    myPort.print(ts);
    myPort.print("    Min = ");
    myPort.println(ts - 180);
    */
  }
  
  if (ts < settings.steeringMin - 2) {
    settings.steeringMax = ts + 180;
    settings.steeringMin = ts;
    
    /*
    myPort.print("New max steering set: Max = ");
    myPort.print(ts + 180);
    myPort.print("    Min = ");
    myPort.println(ts);
    */
  }
}
