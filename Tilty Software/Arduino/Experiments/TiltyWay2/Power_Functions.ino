

/*  Calculates the P, I, and D power values  */
void calcPower() {
  int steering;
  
  //if (abs(ddPitch) >= 200  && abs(ddPitch) < 500 && kP < 25) {  kP += 0.001 * abs(ddPitch) / 200;}
  //if (abs(ddPitch) >= 500 && kP >= 16) {  kP -= 0.0025 * abs(ddPitch) * dT / 200;}
  
  P = kP * pitch;
  I = I + kI * pitch * dT;
  D = (kD * dPitch);
  
  //f_power = 1500 + P + I + D;
  //  Experimental R/C powers
  f_power = P + I + D;
  s_power = -RCsteering;
  /*
  if ((f_power < RCspeed - 10 || f_power > RCspeed + 10) && (pitch_offset > settings.angleOffset - 1.5 || pitch_offset < settings.angleOffset - 1.5)) {
    pitch_offset += 0.00025 * RCspeed;
  }
  else if (pitch_offset < settings.angleOffset - 1.5 || pitch_offset > settings.angleOffset - 1.5) {
    pitch_offset -= 0.000325 * RCspeed;
  }
  */
  
  
  //powerCheck();
  
  /*
  S = map(analogRead(STEERING_SENSE), settings.steeringMin, settings.steeringMax, int(-kS * 500), int(kS * 500));//  Linear power applied steering
  //S = testSteering();//  Sensor based steering (can be twitchy)
  if (abs(S) - abs(s_power - 500) <= 1) {
    s_power = 1500 + S - 8;
  }
  //s_power = 1500 + S;//int(kS * S) + 1;
  //Serial.println(s_power);
  */
}


/*  Checks to be sure that the segway isn't going beyond set maximum speed  */
int forceback = 0;
void powerCheck() {
  /*
  if (abs(f_power - 1500) > speed_limit) {
    if (f_power - 1500 < 0 && ddPitch < 0) {  forceback -= (abs(f_power - 1500) - speed_limit) * kickback;}
    else if (f_power - 1500 > 0 && ddPitch > 0) {  forceback += (abs(f_power - 1500) - speed_limit) * kickback;}
     
    f_power += int(forceback);
  }
  
  else if (abs(forceback) > 0) {
    if (forceback < 0) {  forceback -= (abs(f_power - 1500) - speed_limit) * kickback;}
    else {  forceback += (abs(f_power - 1500) - speed_limit) * kickback;}
    
    f_power += int(forceback);
  }
  */
  if (abs(f_power) > speed_limit) {
    if (f_power < 0) {  forceback = -20 - 5 * (abs(f_power) - speed_limit);}
    if (f_power > 0) {  forceback = 20 + 5 * (abs(f_power) - speed_limit);}
    
    if (forceback + f_power > 500) {  f_power = 500;}
    else if (forceback + f_power < 10-500) {  f_power = -500;}
    else {  f_power += forceback;}
  }
    
  /*
  else if (abs(forceback) > 2) {
    if (forceback > 2) {  forceback -= forceback / 2;}
    else if (forceback < 2) {  forceback += forceback / 2;}
  }
  */
}



void setupServos() {
  f_signal.attach(SPEED_PIN);
  s_signal.attach(STEERING_PIN);
  
  f_signal.writeMicroseconds(1500);
  s_signal.writeMicroseconds(1500);
}

void writePower() {
  //myPort.write(f_power);
  //myPort.println(s_power);
  f_signal.writeMicroseconds(1500 - f_power);
  s_signal.writeMicroseconds(1500 - s_power);
}



float steering_I = 0, steering_P, steering_D;
float steering_kP = 2.0, steering_kI = 0.05, steering_kD = 0.0000033;

int testSteering() {
  int range = 0.075 * 500;
  
  steering_I = steering_I + dYaw * steering_kI * dT;
  steering_D = ddYaw * steering_kD;
  
  /*
  Serial.print("P: ");
  Serial.print(steering_P);
  Serial.print("      I: ");
  Serial.print(steering_I);
  Serial.print("      D: ");
  Serial.print(steering_D);
  Serial.print("    dYaw: ");
  Serial.println(dYaw);
  */
  //if (abs(dYaw) < abs(steering_P)
  //steering_P = map(analogRead(STEERING_SENSE), settings.steeringMin, settings.steeringMax, -range, range);
  //steering_I += map(analogRead(STEERING_SENSE), settings.steeringMin, settings.steeringMax, -range, range) * 0.01;
  return int(steering_P + steering_I + steering_D);
}




//  Experimental R/C code
void remoteControl(char command) {
  //myPort.print(command);
  //myPort.print(": ");
  if (command == FORWARD) {
    RCspeed = int8_t(myPort.read());
    //pitch_offset = settings.angleOffset + RCspeed / 16.0;
    //myPort.println(pitch_offset);
    //f_power += speed;
    //myPort.println(speed);
  }
  if (command == STEERING) {
    RCsteering = int8_t(myPort.read());
    Serial.println(RCsteering);
    //s_power += steering;
    //myPort.println(steering);
  }
}
