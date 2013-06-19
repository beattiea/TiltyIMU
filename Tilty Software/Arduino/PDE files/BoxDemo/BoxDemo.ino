#define pitch 'P'//  Read pitch angle
#define roll 'R'//  Read roll angle
#define yaw 'Y'//  Read yaw angle

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
  while(!Serial) {  IMU.getYawPitchRoll(ypr);}
}

void loop() {
  IMU.getYawPitchRoll(ypr);
  Serial.print(pitch); Serial.println(ypr[1]);
  Serial.print(roll); Serial.println(ypr[2]);
  Serial.print(yaw); Serial.println(ypr[0]);
}

