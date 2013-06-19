/*  Checks that the IMU is connected and communicating  */
void checkIMU() {
  mpu6050.reset();
  delay(50);
  while (!mpu6050.testConnection()) {
    //  Error indication goes here!!!!!!!!!
    if (Serial && millis() % 1000 <= 3) {  Serial.println("IMU connection error!");}
  }
}

/*  Checks the IMU is connected, initializes it, and starts reading it  */
void startIMU() {
  Wire.begin();
  delay(5);
  //checkIMU();//  Checks that IMU is connected and communicable
  IMU.init(true); // the parameter enable or disable fast mode
  
  IMU.getYawPitchRoll(ypr);
  
  pitch = ypr[PITCH] - pitch_offset;
  roll = ypr[ROLL] - roll_offset;
  yaw = ypr[YAW] - yaw_offset;
}

/*  Gets the pitch and roll of the segway  */
void getAngles() {
  IMU.getYawPitchRoll(ypr);
  
  pitch_old = pitch;
  roll_old = roll;
  yaw_old = yaw;
  
  pitch = ypr[PITCH] - pitch_offset;
  roll = ypr[ROLL] - roll_offset;
  yaw = ypr[YAW] - yaw_offset;//  Average yaw drift values calculated in excel
  
  dYaw_old = dYaw;
  dYaw = (yaw - yaw_old) / dT;
  ddYaw_old = ddYaw;
  ddYaw = (dYaw - dYaw_old) / dT;
  
  dPitch_old = dPitch;
  dPitch = (pitch - pitch_old) / dT;
  ddPitch_old = ddPitch;
  ddPitch = (dPitch - dPitch_old) / dT;
  
  dRoll_old = dRoll;
  dRoll = (roll - roll_old) / dT;
  ddRoll_old = ddRoll;
  ddRoll = (dRoll - dRoll_old) / dT;
}


float average = 10.5;
int below = 0, above = 0;
unsigned long iter = 0;

void testPIDtune() {
  
  Serial.print("Below: ");
  Serial.print(below);
  Serial.print("   Above: ");
  Serial.print(above);
  Serial.print("      kP: ");
  Serial.println(kP, 3);
  //Serial.print("   ddPitch: ");
  //Serial.println(ddPitch, 3);
  //if ((pitch > 0 && ddPitch > 0) || (pitch < 0 && ddPitch < 0)) {
    if (abs(ddPitch) < 250 && kP < settings.kP * 4) {  kP += (0.5 / (abs(ddPitch) + 1)); below += 1;}//  worked well at 0.5
    if (abs(ddPitch) > 2750 && kP > 0) {  kP -= (abs(ddPitch) / 250000) * abs(dPitch); above += 1; buzzerOn();}//  worked well at 5000
    else {  buzzerOff();}
  //}
  iter += 1;
  average = (average * (iter - 1) + kP) / iter;
  //if (abs(ddPitch) < 200 && kD < settings.kD * 2.5 && abs(pitch) > 1) {  kD += 0.0075 / abs(ddPitch);}
  //if (abs(ddPitch) > 750 && kD > settings.kD) {  kD -= abs(ddPitch) / 10000000;}
  
  if (kP < settings.kP) {  kP = settings.kP;}
  //if (kP < settings.kP) {  kP = settings.kP;}
}
