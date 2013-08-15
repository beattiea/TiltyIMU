
#include <FastServo.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>

/*  IMU includes  */
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <I2Cdev.h>
#include <MPU60X0.h>

FreeIMU IMU = FreeIMU();
MPU60X0 mpu6050 = MPU60X0();

float val[9], q[4], ypr[3];// float arrays to retrieve IMU data fro freeIMU
float yaw, pitch, roll;
float accel, d_accel;
float d_yaw, d_pitch, d_roll;
float P = 0.0, I = 0.0, D = 0.0;

int pitch_power = 0;
int roll_power = 0;
int rise_power = 825;

Servo front, back, left, right;

void setup() {
  while (!Serial) {  }
  
  startIMU();
  front.attach(3);
  back.attach(4);
  left.attach(5);
  right.attach(6);
  
  while (!Serial) {
    front.writeMicroseconds(1000);
    getAngles();
  }
  
  Serial.println("Starting motor...");
  
  while (!Serial.available()) {  
    getAngles();
    Serial.println(pitch);
    front.writeMicroseconds(1100);
  }
}

void loop() {
  getAngles();
  Serial.print("Pitch: ");
  Serial.print(pitch, 3);
  
  writePower();
  
  /*
  Serial.print("    Roll: ");
  Serial.print(roll, 3);
  Serial.print("    Yaw: ");
  Serial.print(yaw, 3);
  Serial.print("    Accel: ");
  Serial.print(accel);
  */
  Serial.print("    P: ");
  Serial.print(P, 2);
  Serial.print("    I: ");
  Serial.print(I, 2);
  Serial.print("    D: ");
  Serial.print(d_pitch, 2);
  Serial.println();
  
  delay(4);
  
  while (abs(roll) > 15 || !Serial || pitch > 35) {
    front.writeMicroseconds(1000);
    getAngles();
    I = 0;
  }
}




float kP = 30.0, kI = 25.0, kD = .25;
float kP_rise, kI_rise, kD_rise;

void writePower() {
  //  Pitch PID  //
  if (abs(kP * pitch) < 25) {
    P = pitch * kP;
  }
  
  float I_temp = (pitch * kI) * 0.005;
  if (abs(I + I_temp) < 20) {
    I += I_temp;
  }
  //D = d_pitch * kD;
  pitch_power = P + I + D;
  
  //  Roll PID  //
  /*
  P = roll * kP;
  I = I + roll * kI;
  D = d_roll * kD;
  roll_power = P + I + D;
  */
  
  //  Rise PID  //
  //if (abs(pitch) < 3 && abs(roll) < 3) {
    /*
  if (abs(accel) > 2000) {
    P = accel * -kP_rise;
    I = I + accel * -kI_rise;
    D = d_accel * -kD_rise;
    rise_power = P + I + D;
  }
  */
  
  front.writeMicroseconds(1000 - pitch_power + rise_power);
  back.writeMicroseconds(1000 - pitch_power + rise_power);
  left.writeMicroseconds(1000 + roll_power + rise_power);
  right.writeMicroseconds(1000 - roll_power + rise_power);
}
