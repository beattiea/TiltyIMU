/*  Tests multiplexer connection to default connections  */
void testMux() {
  /*
  for (int i = 0; i < 7; i++) {
    Serial.print("Value of DIP ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(mux.muxDigitalRead(i));
  }
  */
  /*
  for (int i = 12; i < 16; i++) {
    Serial.print("Value of trimm R");
    Serial.print(i - 9);
    Serial.print(": ");
    Serial.println(mux.analogRead(i));
  }
  
  Serial.print("Value of battery sensing: ");
  Serial.println(mux.analogRead(BATT));
  */
  /*
  for (int i = 0; i < 16; i++) {
    Serial.print("Value of MUX ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(mux.readPin(i));
  }
  Serial.println();
  delay(1000);
  */
  //Serial.println(mux.muxDigitalRead(0));
}



void testLED() {
  //attachTimerInterrupt(0, blink, 1000);
  if (f_power > 1500) {//  Green on bi-directional LED
    analogWrite(5, map(f_power, 1500, 2000, 0, 255));
    digitalWrite(6, LOW);
  }
  if (f_power < 1500) {//  Red on bi-directional LED
    analogWrite(6, map(f_power, 1000, 1500, 255, 0));
    digitalWrite(5, LOW);
  }
}



/*  Checks to see if IMU will initialize and connect  */
boolean testIMUconnection() {
  long start = millis();
  
  IMU.init(true);  // Initializes and tests the IMU in 400kHz fast mode
  while (!mpu6050.testConnection() && millis() - start < 5000) {};
  if (mpu6050.testConnection()) {
    Serial.println("IMU is connected in fast mode");
    return true;
  }
  
  start = millis();
  IMU.init(false);  // Initializes and tests the IMU at regular speed
  while (!mpu6050.testConnection() && millis() - start < 5000) {};
  if (mpu6050.testConnection()) {
    Serial.println("IMU is connected in regular mode");
    return true;
  }
  
  Serial.println("IMU is not connecting!!!!!!!!!!!!");
  return false;
}

/*  Prints IMU yaw, pitch, and roll readings  */
void testIMUreading() {
  IMU.getYawPitchRoll(ypr);
  Serial.print("Yaw: ");
  Serial.println(ypr[YAW]);
  Serial.print("Pitch: ");
  Serial.println(ypr[PITCH]);
  Serial.print("Roll: ");
  Serial.println(ypr[ROLL]);
  Serial.println();
}
