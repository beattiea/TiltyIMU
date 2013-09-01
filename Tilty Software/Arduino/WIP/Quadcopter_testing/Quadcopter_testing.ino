#define DEBUG_INITS
#define INCLUDE_DMP

#include "TiltyIMU.h"
#include "i2c_t3.h"
#include "I2Cdev.h"
#include "PID.h"
#include "Servo.h"
//#include "RCsignal.h"

#include <SatelliteRX.h>

SatelliteRX rx = SatelliteRX(Serial3);// Use Serial3 with RX pin 7. Must define a pin to be able to bind the receiver.

float kP = 25;
float kI = 25;
float kD = 0.0;

float iMax = 15;

TiltyIMU tiltyIMU;

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

PID pitchPID;
PID rollPID;

float ypr[3];

float dPitch = 0;
float dRoll = 0;

float pitchValue;
float rollValue;

float pitchOffset = 2.74;
float rollOffset = 0.22;

float d_pitchValue = 0;
float d_rollValue = 0;

int d_throttle = 0;

int min_throttle = 75;

float voltage;

volatile int throttle;
//RCsignal throttleRC(21, updateThrottle);

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
  
  pitchPID = PID(&dPitch, &pitchValue, kP, kI, kD, FORWARD);
  rollPID = PID(&dRoll, &rollValue, kP, kI, kD, FORWARD);
  
  //pitchPID = PID(&ypr[1], &d_pitchValue, kP, kI, kD, REVERSE);
  //rollPID = PID(&ypr[2], &d_rollValue, kP, kI, kD, REVERSE);
  
  pitchPID.setLimits(-25, 25);
  rollPID.setLimits(-25, 25);
  pitchPID.setILimits(-iMax, iMax);
  rollPID.setILimits(-iMax, iMax);
  pitchPID.setInputConstraints(-2.5, 2.5);
  rollPID.setInputConstraints(-2.5, 2.5); 
  
  rx.init();
  
  for(int i = 0; i < 1000; i++){
	 tiltyIMU.updateSensors();
	 delay(5);
	 digitalWrite(13, LOW);
	 Serial.println("Zeroing...");
	 tiltyIMU.readAngles(ypr);
	 Serial.println(ypr[2]);
	 if (i % 100 == 0) {digitalWrite(13, !digitalRead(13));}
	voltage = (analogRead(14) / 1024.0) * 51.8294;
	Serial.println(voltage);
  }
  
	tiltyIMU.readAngles(ypr);
  
	digitalWrite(13, HIGH);
	while(throttle > 150){};
	d_throttle = throttle;
	
	while (rx.channel_data[AUX1] == 0) {
		rx.readData();
	}
	
	digitalWrite(13, LOW);
}

/*
void updateThrottle() {
  throttle = throttleRC.read();
}
*/

void loop() {
	
  rx.readData();
  
  throttle = constrain(rx.channel_data[THROTTLE] - 153, 0, 500);
	
  tiltyIMU.updateSensors();
  
  if (tiltyIMU.imu_updated) {
  	dPitch = ypr[1];
 	dRoll = ypr[2];
  	
  	delay(5);
  	
	tiltyIMU.readAngles(ypr);
	 
	ypr[1] -= pitchOffset;
 	ypr[2] -= rollOffset;
 	 
 	dPitch -= ypr[1];
 	dRoll -= ypr[2];
 	
 	dPitch += (rx.channel_data[ELEVATOR] - 511) / 1000.0;
	dRoll += (rx.channel_data[AILERON] - 511) / 1000.0;
 	
 	//pitchPID.update();
 	//rollPID.update();
 	/*
 	Serial.print("Throttle: ");
  	Serial.print(throttle);
  
	Serial.print("\t\t");
	Serial.print(dPitch);
	Serial.print("\t");
	Serial.print(dRoll);
	
	Serial.print("\t\t");
	Serial.print(rollPID.Ivalue);
	Serial.println();
	*/
  }
  
  voltage = (analogRead(14) / 1024.0) * 51.8294;
  
	  if((throttle > min_throttle && throttle != 0 && throttle < 1000) && (abs(ypr[1]) < 45 && abs(ypr[2]) < 45) && rx.channel_data[AUX1] > 300) //check to make sure that we have a "real" throttle value, and that we're not changing at too much of an angle
	  { 
		  pitchPID.update();
		  rollPID.update();
		  
		  //Serial.print(dPitch);
		  //Serial.print(", ");
		  //Serial.print(pitchPID.Pvalue);
		  //Serial.print(", ");
		  //Serial.print(pitchPID.Ivalue, 5);
		  //Serial.print(", ");
		  //Serial.print(pitchPID.Dvalue);
		  //Serial.print("\tr\t\t");
		  Serial.print(dRoll, 2);
		  //Serial.print(", ");
		  //Serial.print(rollPID.Pvalue);
		  Serial.print(", ");
		  Serial.print(rollPID.Ivalue, 5);
		  //Serial.print(", ");
		  //Serial.print(rollPID.Dvalue);
		  Serial.println();
		  
		  
		  pitchValue *= voltage / 12.3;
		  rollValue *= voltage / 12.3;
		  
		  /*
		  Serial.print("Pitch PID: ");
		  Serial.print(pitchValue);
		  Serial.print("\t\tRoll PID: ");
		  Serial.print(rollValue);
		  Serial.println();
		  */
		  
		  /*
		  Serial.print("Remote Data: ");
		  Serial.print(pitchValue);
		  Serial.print("\t");
		  Serial.print(rollValue);
		  Serial.println();
		  */
		  	
		  ESC1.writeMicroseconds(1000 + throttle - pitchValue - rollValue);
		  ESC2.writeMicroseconds(1000 + throttle + pitchValue - rollValue);
		  ESC3.writeMicroseconds(1000 + throttle + pitchValue + rollValue);
		  ESC4.writeMicroseconds(1000 + throttle - pitchValue + rollValue);
	  }
	  else{
		  ESC1.writeMicroseconds(1000);
		  ESC2.writeMicroseconds(1000);
		  ESC3.writeMicroseconds(1000);
		  ESC4.writeMicroseconds(1000);
		  if (rx.channel_data[AUX2] >= 300) {
		  	
		  	Serial.println("Reset!");
			  pitchPID.reset();
			  rollPID.reset();
		  }
	  }
}


