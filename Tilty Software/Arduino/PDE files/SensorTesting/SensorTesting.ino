#define PITCH_ 'P'//  Read pitch angle
#define ROLL_ 'R'//  Read roll angle
#define YAW_ 'Y'//  Read yaw angle
#define BATT_ 'B'//  Read battery voltage
#define ALT_ 'A'//  Read altitude
#define TEMP_ 'T'//  Read temperature
#define ZERO_ 'Z'//  Zero IMU gyro

#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <I2Cdev.h>
#include <MPU60X0.h>
#include <HMC58X3.h>
#include <MPL3115A2.h>

FreeIMU IMU = FreeIMU();
MPL3115A2 altimeter;

float ypr[3];
float altitude, temperature;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(10);
  altimeter.init();
  IMU.init(true);
  Serial.println("IMU intialized");
  while(!Serial) {  IMU.zeroGyro();}
  
}

float yaw_offset = 0;
float pitch_offset = 0;
float roll_offset = 0;
float alt_offset = 0;

void loop() {
  IMU.getYawPitchRoll(ypr);
  if (altimeter.checkData()) {
    altitude = altimeter.readAltitudeM();
    temperature = altimeter.readTempC();
  }
  Serial.print(ROLL_); Serial.println(ypr[2] - roll_offset, 2);
  Serial.print(PITCH_); Serial.println(ypr[1] - pitch_offset, 2);
  Serial.print(YAW_); Serial.println(-ypr[0] - yaw_offset, 2);
  Serial.print(BATT_); Serial.println(analogRead(14) * 0.003223, 1);
  Serial.print(ALT_); Serial.println(altitude - alt_offset, 2);
  Serial.print(TEMP_); Serial.println(temperature, 2);
  
  if (Serial.available()) {
    char data = Serial.read();
    if (data == YAW_) {  yaw_offset = ypr[0];}
    if (data == PITCH_) {  pitch_offset = ypr[1];}
    if (data == ROLL_) {  roll_offset = ypr[2];}
    if (data == ALT_) {  alt_offset = altitude;}
    if (data == ZERO_) {}  //IMU.zeroGyro();}
  }
}

