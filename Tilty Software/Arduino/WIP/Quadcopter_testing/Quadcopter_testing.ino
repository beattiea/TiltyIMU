#define DEBUG_INITS
#define INCLUDE_DMP

#include "TiltyIMU.h"
#include "i2c_t3.h"
#include "I2Cdev.h"
#include "PID.h"
#include "Servo.h"
#include "RCsignal.h"

float kP = 5.0;
float kI = 0.0;
float kD = 0.5;

float iMax = 8;

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

float pitchOffset = 2.74;
float rollOffset = 0.22;

float d_pitchValue = 0;
float d_rollValue = 0;

int d_throttle = 0;

float voltage;

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
  rollPID = PID(&ypr[2], &rollValue, kP, kI, kD, REVERSE);
  
  //pitchPID = PID(&ypr[1], &d_pitchValue, kP, kI, kD, REVERSE);
  //rollPID = PID(&ypr[2], &d_rollValue, kP, kI, kD, REVERSE);
  
  //pitchPID.setLimits(-20, 20);
  //rollPID.setLimits(-20, 20);
  pitchPID.setILimits(-iMax, iMax);
  rollPID.setILimits(-iMax, iMax);
  
  for(int i = 0; i < 1000; i++){
	 tiltyIMU.updateIMU();
	 digitalWrite(13, LOW);
	 Serial.println("Zeroing...");
	 if (i % 100 == 0) {digitalWrite(13, !digitalRead(13));}
	voltage = (analogRead(14) / 1024.0) * 51.8294;
	Serial.println(voltage);
  }
  tiltyIMU.readAngles(ypr);
  
	digitalWrite(13, HIGH);
	while(throttle > 1150){};
	d_throttle = throttle;
}

void updateThrottle() {
  throttle = throttleRC.read();
  
}

void loop() {
	d_pitchValue = ypr[1];
	d_rollValue = ypr[2];
	
  tiltyIMU.updateIMU();
  tiltyIMU.readAngles(ypr);
  
  ypr[1] -= pitchOffset;
  ypr[2] -= rollOffset;
  
  d_pitchValue -= ypr[1];
  d_rollValue -= ypr[2];
  
  voltage = (analogRead(14) / 1024.0) * 51.8294;
  
  //Serial.println(throttle);
  
	  if((throttle > 1200 && throttle != 0 && throttle < 2000) && (abs(ypr[1]) < 25 && abs(ypr[2]) < 25)) //check to make sure that we have a "real" throttle value, and that we're not changing at too much of an angle
	  { 
		  pitchPID.update();
		  rollPID.update();
		  
		  Serial.print(ypr[1]);
		  Serial.print(", ");
		  Serial.print(pitchPID.Pvalue);
		  Serial.print(", ");
		  Serial.print(pitchPID.Ivalue);
		  Serial.print(", ");
		  Serial.print(pitchPID.Dvalue);
		  Serial.print(", ");
		  Serial.print(ypr[2]);
		  Serial.print(", ");
		  Serial.print(rollPID.Pvalue);
		  Serial.print(", ");
		  Serial.print(rollPID.Ivalue);
		  Serial.print(", ");
		  Serial.print(rollPID.Dvalue);
		  Serial.println();
		  
		  pitchValue *= voltage / 12.3;
		  rollValue *= voltage / 12.3;
		  	
		  ESC1.writeMicroseconds(throttle + pitchValue + rollValue);
		  ESC2.writeMicroseconds(throttle - pitchValue - rollValue);
		  ESC3.writeMicroseconds(throttle + pitchValue - rollValue);
		  ESC4.writeMicroseconds(throttle - pitchValue + rollValue);
	  }
	  else{
		  ESC1.writeMicroseconds(1000);
		  ESC2.writeMicroseconds(1000);
		  ESC3.writeMicroseconds(1000);
		  ESC4.writeMicroseconds(1000);
		  pitchPID.reset();
		  rollPID.reset();
	  }
}


