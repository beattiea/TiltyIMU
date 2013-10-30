#define PITCH_ 'P'//  Read pitch angle
#define ROLL_ 'R'//  Read roll angle
#define YAW_ 'Y'//  Read yaw angle
#define BATT_ 'B'//  Read battery voltage
#define ALT_ 'A'//  Read altitude
#define TEMP_ 'T'//  Read temperature
#define ZERO_ 'Z'//  Zero IMU gyro

//#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <I2Cdev.h>
#include <MPU6050.h>
#include <HMC5883.h>
#include <i2c_t3.h>

FreeIMU IMU = FreeIMU();
float ypr[3];
float altitude, temperature;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(10);
  IMU.init(true);
  Serial.println("IMU intialized");
  //while(!Serial) {  IMU.zeroGyro();}
  sensorConfig();
  
  if(IIC_Read(0x0C) == 196); //checks who_am_i bit for basic I2C handshake test
  else Serial.println("i2c bad");
}

float yaw_offset = 0;
float pitch_offset = 0;
float roll_offset = 0;
float alt_offset = 0;

void loop() {
  IMU.getYawPitchRoll(ypr);
  if (check_new()) {  sensorReadData();}
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

