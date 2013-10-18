

/*  Calculates the P, I, and D power values  */
void calcPower() {
  int steering;
  float dT = loop_time / 1000.0;
  
  if (abs(pitch) >= 20) {  kP = settings.kP + abs(pitch) / 17.5;}
  
  P = kP * pitch;
  I = I + kI * pitch * dT;
  D = (kD * (pitch - pitch_old)) / dT;
  
  if (abs(P+I+D) >= 250) {
    I += kI * pitch * dT * ((abs(P+I+D) - 150) / 50.0);
    
    if (abs(P+I+D) >= 250 && abs(P+I+D) < 400) {  buzzerPulse(750);}
    if (abs(P+I+D) >= 400) {  buzzerPulse(100);}
  }
  else {  buzzerOff();}
  f_power = 1500 + P + I + D;
  
  //S = map(analogRead(STEERING_SENSE), settings.steeringMin, settings.steeringMax, -500, 500);
  S = testSteering();
  s_power = 1500 + S;// + int(kS * S)  + 1;
  //Serial.println(s_power);
}

/*  Checks to be sure that the segway isn't going beyond set maximum speed  */
void powerCheck() {
  
}



void setupServos() {
  f_signal.attach(SPEED_PIN);
  s_signal.attach(STEERING_PIN);
  
  f_signal.writeMicroseconds(1500);
  s_signal.writeMicroseconds(1500);
}

void writePower() {
  f_signal.writeMicroseconds(f_power);
  s_signal.writeMicroseconds(s_power);
}
