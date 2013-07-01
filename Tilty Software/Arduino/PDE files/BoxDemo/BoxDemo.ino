#define pitch 'P'//  Read pitch angle
#define roll 'R'//  Read roll angle
#define yaw 'Y'//  Read yaw angle
#define batt 'B'//  Read battery voltage

#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <I2Cdev.h>
#include <MPU60X0.h>

FreeIMU IMU = FreeIMU();
float ypr[3];

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(10);
  IMU.init(true);
  while(!Serial) {  IMU.zeroGyro();}
}

float yaw_offset = 0;
float pitch_offset = 0;
float roll_offset = 0;

void loop() {
  IMU.getYawPitchRoll(ypr);
  Serial.print(roll); Serial.println(ypr[1] - roll_offset, 2);
  Serial.print(pitch); Serial.println(ypr[2] - pitch_offset, 2);
  Serial.print(yaw); Serial.println(-ypr[0] - yaw_offset, 2);
  Serial.print(batt); Serial.println(analogRead(14) * 0.003223, 1);
  
  if (Serial.available()) {
    char data = Serial.read();
    if (data == 'y') {  yaw_offset = ypr[0];}
    if (data == 'p') {  pitch_offset = ypr[2];}
    if (data == 'r') {  roll_offset = ypr[1];}
    if (data == 'z') {  IMU.zeroGyro();}
    if (data == '|') {  Serial.println('|');}
  }
}

