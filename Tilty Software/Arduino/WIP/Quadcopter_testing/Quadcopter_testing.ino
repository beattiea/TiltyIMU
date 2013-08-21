#define DEBUG_INITS
#define INCLUDE_DMP

#include "TiltyIMU.h"
#include "i2c_t3.h"
#include "I2Cdev.h"
#include "PID.h"
#include "Servo.h"
#include "RCsignal.h"

#define kP 1
#define kI 0.01
#define kD 0.2

TiltyIMU tiltyIMU;

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

PID pitchPID;
PID rollPID;

float ypr[3];

float pitchValue;
float rollValue;

float pitchOffset = 3.08;
float rollOffset = .85;

volatile int throttle;
RCsignal throttleRC(21, updateThrottle);

void setup(){
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(115200);
  
  delay(25);
  
  //while (!Serial) {}
  
  tiltyIMU = TiltyIMU();
  tiltyIMU.init();
  
  ESC1.attach(2);
  ESC2.attach(3);
  ESC3.attach(22);
  ESC4.attach(23);
  
  ESC1.writeMicroseconds(1000);
  ESC2.writeMicroseconds(1000);
  ESC3.writeMicroseconds(1000);
  ESC4.writeMicroseconds(1000);
  
  pitchPID = PID(&ypr[1], &pitchValue, kP, kI, kD, REVERSE);
  rollPID = PID(&ypr[3], &rollValue, kP, kI, kD, REVERSE);
  
  pitchPID.setLimits(-20, 20);
  rollPID.setLimits(-20, 20);
  pitchPID.setILimits(-7.5, 7.5);
  rollPID.setILimits(-7.5, 7.5);
  
  for(int i = 0; i < 1000; i++){
	 tiltyIMU.updateIMU();
	 digitalWrite(13, LOW);
	 Serial.println("Zeroing...");
	 if (i % 100 == 0) {digitalWrite(13, !digitalRead(13));}
  }
  tiltyIMU.readAngles(ypr);
  
  //pitchOffset = ypr[1];
  //rollOffset = ypr[2];
  
  digitalWrite(13, HIGH);
   while(throttle > 1150){};

}

void updateThrottle() {
  throttle = throttleRC.read();
  
}

void loop(){
  
  //Serial.println(ypr[1]);
  //Serial.println(ypr[2]);
  
  tiltyIMU.updateIMU();
  tiltyIMU.readAngles(ypr);
  
  ypr[1] -= pitchOffset;
  ypr[2] -= rollOffset;
  
  Serial.println(throttle);
  
  if((throttle > 1200 && throttle != 0 && throttle < 2000) && (abs(ypr[1]) < 15 && abs(ypr[2]) < 15)) //check to make sure that we have a "real" throttle value, and that we're not changing at too much of an angle
  { 
  pitchPID.update();
  rollPID.update();
  	
  ESC1.writeMicroseconds(throttle + pitchValue + rollValue);
  ESC2.writeMicroseconds(throttle + pitchValue - rollValue);
  ESC3.writeMicroseconds(throttle - pitchValue - rollValue);
  ESC4.writeMicroseconds(throttle - pitchValue + rollValue);
  }
  else{
  ESC1.writeMicroseconds(1000);
  ESC2.writeMicroseconds(1000);
  ESC3.writeMicroseconds(1000);
  ESC4.writeMicroseconds(1000);
  }
}


