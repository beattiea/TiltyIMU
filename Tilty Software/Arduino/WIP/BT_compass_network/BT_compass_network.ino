#include <i2c_t3.h>
#include <HMC5883.h>
#include <MPL3115A2.h>

#include <I2Cdev.h>
//#include <MPU6050.h>
#include "MPU6050_6Axis_MotionApps20.h"

#define MASTER
//#define SLAVE

#define slave1 "98D3,31,B0466B"
#define slave2 "98D3,31,B045DB"

// Instantiate the sensors
MPU6050 imu;
HMC5883 compass;

float ypr[3], ypr_radians[3];
float compass_data[3];
#define YAW 0
#define PITCH 1
#define ROLL 2

void setup() {
	Serial.begin(115200);
    Serial1.begin(115200);

	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);

	imu.reset();
	delay(25);
	
	setupIMU();
	compass.init();
}

void loop() {
    //connectToSlave(slave1);

	if (imu.getIntDataReadyStatus()) {
		readIMU();
	}
	
	if (compass.getDataReady()) {
		compass.getValues(compass_data);
	}
	
	//debugIMU();
	debugCompass();
}

void debugIMU() {
	Serial.print("Y: ");	Serial.print(ypr[0]);
	Serial.print("\tP: ");	Serial.print(ypr[1]);
	Serial.print("\tR: ");	Serial.print(ypr[2]);
	Serial.println();
}

void debugCompass() {
	Serial.print("X: ");	Serial.print(compass_data[0]);
	Serial.print("\tY: ");	Serial.print(compass_data[1]);
	Serial.print("\tZ: ");	Serial.print(compass_data[2]);
	Serial.print("\tHeading: ");	//Serial.print(atan(compass_data[0] / compass_data[1]) * 180 / PI);
	Serial.print(tiltCompensateCompass(compass_data));
	Serial.println();
}