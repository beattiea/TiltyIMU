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
