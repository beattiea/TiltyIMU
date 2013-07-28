#define YAW 0
#define PITCH 2
#define ROLL 1

/*  Checks the IMU is connected, initializes it, and starts reading it  */
void startIMU() {
  Wire.begin();
  delay(5);
  //checkIMU();//  Checks that IMU is connected and communicable
  IMU.init(true); // the parameter enable or disable fast mode
  
  mpu6050.setInterruptDrive(0);
  mpu6050.setMotionDetectionThreshold(2);
  mpu6050.setZeroMotionDetectionThreshold(156);
  mpu6050.setMotionDetectionDuration(80);
  mpu6050.setZeroMotionDetectionDuration(0);
  
  Serial.print("Motion interrupt enabled: ");
  Serial.println(mpu6050.getIntMotionEnabled());
  Serial.print("Motion detection threshold: ");
  Serial.println(mpu6050.getMotionDetectionThreshold());
  Serial.print("Motion detection duration: ");
  Serial.println(mpu6050.getMotionDetectionDuration());
  Serial.print("Motion detected: ");
  Serial.println(mpu6050.getZeroMotionDetected());
  
  while (true) {
    
  }
  
  IMU.getYawPitchRoll(ypr);
  
  pitch = ypr[PITCH];
  roll = ypr[ROLL];
  yaw = ypr[YAW];
}

/*  Gets the pitch and roll of the segway  */
void getAngles() {
  IMU.getYawPitchRoll(ypr);
  
  d_pitch = (ypr[PITCH] - pitch) * 200;
  
  pitch = ypr[PITCH];
  roll = ypr[ROLL];
  yaw = ypr[YAW];
}
