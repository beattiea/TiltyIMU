/*  Standard Arduino library includes  */
#include <i2c_t3.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Servo.h>

/*  IMU includes  */
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <I2Cdev.h>
#include <MPU6050.h>

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
float kP, kI, kD, P=0, I=0, D=0, kS, S;
int f_power = 1500, s_power = 1500;
int steering_min , steering_max;
int speed_limit, kickback;
long start, stop;
int loop_time = 5, time;
boolean connected = false;
#define BUZZER 2
#define SPEED_PIN 5//  PWM1
#define STEERING_PIN 6//  PWM2
#define STEERING_SENSE 14

#define DEBUG

Settings settings, test;
Servo f_signal;//  Forward/back signal
Servo s_signal;//  Steering signal

void setup()
{
  setupPins();
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  //Serial.begin(115200);
  
  myPort.begin(115200);

  loadSavedSettings();

  setupServos();
  //while (!connected) {  checkSerial();}
  
  startIMU();
  
  for (int i = 0; i < 250; i++) {
    getAngles();
    buzzerPulse(250);
    //myPort.println(pitch, 2);
    delay(10);
  }
}

void loop()
{
  checkSerial();
  
  getAngles();
  
  if (abs(pitch) < 35 && abs(roll) < 45 && abs(P+I+D) < 500) {
    calcPower();
    writePower();
  }
  else {
    while (abs(pitch) > 5 || abs(roll) > 10) {
      buzzerOn();
      checkSerial();
      getAngles();
      
      buzzerOff();
      f_signal.writeMicroseconds(1500);
      s_signal.writeMicroseconds(1500);
      s_power = 1500;
      f_power = 1500;
      P = 0;
      I = 0;
      D = 0;
    }
    buzzerOff();
    /*  Code to auto adjust the angle offset of the baby segway to keep it from accelerating on its own  */
    //  Doesn't really do anything now
    //if (abs(pitch) <= 5 && abs(P+I+D) >= 100) {  pitch_offset -= (abs(pitch) / pitch) * 0.01;}
  }
  
  killTime();
  //myPort.println(killTime());//  Kills time till the next loop should begin
}

/*  Calculates the amount of time left in the loop and waits for it to expire  */
int killTime() {
  long delay = 0;
  while (millis() - start < loop_time) {
    delayMicroseconds(10);
    delay += 10;
  }
  start = millis();
  return delay;
}
