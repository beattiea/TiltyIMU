/*  Standard Arduino library includes  */
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <FastServo.h>

/*  IMU includes  */
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <I2Cdev.h>
#include <MPU60X0.h>

/*  Custom Library Includes  */
#include <Multiplexer.h>
#include <TeensyTimerInterrupts.h>
#include <Settings.h>

/*  Definition File Includes  */
#import "Mux_Definitions.h"
#import "EEPROM_Definitions.h"
#import "IMU_Definitions.h"
#import "Serial_Definitions.h"

/*  Global Variable Declarations  */
float pitch, roll, yaw;// Forward and Sideways tilt angles
float pitch_old, roll_old, yaw_old;//  Forward and sideways tilt angles from previous reading

/*  Temporary variables (need to be moved?)  */
float kP, kI, kD, P=0, I=0, D=0, kS, S, PID_old = 0;
float kickback = 0.25;
int max_speed = 500, speed_limit;
int f_power = 1500, s_power = 1500;
int steering_min , steering_max;
long start, stop, loop_start;
int loop_time = 5, time;
float dT = loop_time / 1000.0;
boolean connected = false;
#define BUZZER 2
#define SPEED_PIN 3//  PWM1
#define STEERING_PIN 4//  PWM2
#define STEERING_SENSE 14

#define DEBUG

Settings settings, test;
Servo f_signal;//  Forward/back signal
Servo s_signal;//  Steering signal

void setup()
{
  setupPins();
  
  myPort.begin(115200);

  loadSavedSettings();
  
  setupServos();
  
  //while(!Serial) {}
  
  startIMU();
  /*
  start = millis();
  while (abs(dPitch) >= 0.005) {  
    calibrateIMU();
    buzzerPulse(500);
    delay(10);
  }
  myPort.print("Done! Time: ");
  myPort.println(millis() - start);
  */
  
  for (int i = 0; i < 500; i++) {
    getAngles();
    buzzerPulse(250);
    killTime();
  }
  
  
  while (analogRead(STEERING_SENSE) > (settings.steeringMin + settings.steeringMax) / 2 + 10 || analogRead(STEERING_SENSE) < (settings.steeringMin + settings.steeringMax) / 2 - 10) {  
    buzzerPulse(500);
    checkSerial();
    getAngles();
    
    killTime();
  }
  buzzerOff();
  
  while (abs(pitch) > 1) {
    buzzerPulse(500);
    kP = 5;
    kI = 1;
    kD = 0.1;
    checkSerial();
    getAngles();
    calcPower();
    writePower();
    killTime();
  }
  
  kP = settings.kP;
  kI = settings.kI;
  kD = settings.kD;
  P = 0;
  I = 0;
  D = 0;
}

void loop()
{
 
  checkSerial();
  
  getAngles();
  
  //steeringCheck();
  
  if (abs(pitch) < 25 && abs(roll) < 35 && abs(f_power - 1500) < max_speed) {
    if (abs(P+I+D) > max_speed * 0.75) {  buzzerOn();}
    else if (abs(f_power - 1500) > speed_limit) {  buzzerPulse(50);}
    //else if (abs(f_power - 1500) > speed_limit * 0.75 && abs(f_power - 1500) < speed_limit) {  buzzerPulse(100);}
    else {  buzzerOff();}
    PID_old = P+I+D;
    calcPower();
    //testPIDtune();
    writePower();
  }
  else {
    while (true) {//  If anything goes drastically wrong the segway must be rebooted but can still be read from
      buzzerOn();
      checkSerial();
      getAngles();
      
      if (f_power < 1500) {  f_power += 1;}
      if (f_power > 1500) {  f_power -= 1;}
      if (s_power < 1500) {  s_power += 1;}
      if (s_power > 1500) {  s_power -= 1;}
      
      f_signal.writeMicroseconds(f_power);
      s_signal.writeMicroseconds(s_power);
      
      killTime();
    }
  }
  
  killTime();
  //myPort.println(killTime());//  Kills time till the next loop should begin
}

/*  Calculates the amount of time left in the loop and waits for it to expire  */
int killTime() {
  long delay = 0;
  
  while (millis() - loop_start < loop_time) {
    delayMicroseconds(10);
    delay += 10;
  }
  loop_start = millis();
  return delay;
}
