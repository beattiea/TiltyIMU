#include <i2c_t3.h>
#include <HMC5883.h>
#include <MPL3115A2.h>

#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"

//#include <AHRS.h>

#define MASTER
//#define SLAVE

// Board bluetooth addresses
#define board1 "98D3,31,B0339B" // White
#define board2 "98D3,31,B045D7" // Red
#define board3 "98D3,31,B033C0" // Green

#define bt_cmd 15 // Bluetooth command pin


// Instantiate the sensors
MPU6050 imu;
HMC5883 compass;

float ypr[3], ypr_radians[3];
float compass_data[3];
float xh, yh;
#define YAW 0
#define PITCH 1
#define ROLL 2

float gyro_off, heading;
int16_t yaw_map[360];

void setup() {
	Serial.begin(115200);
    Serial1.begin(115200);
	pinMode(bt_cmd, OUTPUT);
	pinMode(13, OUTPUT);


	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);
	imu.reset();

	delay(250);
	
	setupIMU();
	compass.init();

    while (!Serial) {}
    Serial.println("Begin!");
	
	for (int i = 0; i < 10; i) {
		if (imu.getIntDataReadyStatus()) {
			readIMU();
			debugIMU();
			i++;
		}
	}
	
	while (abs(ypr[PITCH]) > 1 && abs(ypr[ROLL]) > 1) {
		if (imu.getIntDataReadyStatus()) {
			readIMU();
			debugIMU();
		}
		if (compass.getDataReady()) {
			digitalWrite(13, abs(ypr[PITCH]) < 1 && abs(ypr[ROLL]) < 1 ? HIGH : LOW);
			heading = tiltCompensateCompass(compass_data);
			if (abs(ypr[PITCH]) < 1 && abs(ypr[ROLL]) < 1) {
				int yaw_heading = map(ypr[YAW], -180, 180, 360, 0);
				for (int i = 0; i < 360; i++) {
					int index;
					if (yaw_heading + i < 360) {	index = yaw_heading + i;}
					else {	index = yaw_heading + i - 360;}

					int int_heading = int(heading);
					if (int_heading + i < 360) {	yaw_map[index] = int_heading + i;}
					else {	yaw_map[index] = int_heading + i - 360;}
				}
			}
		}
	}

}

bool print = false;
unsigned long count = 0;

void loop() {
	if (imu.getIntDataReadyStatus()) {
		readIMU();
	}

	if (compass.getDataReady()) {
		compass.getValues(compass_data);
		calibrateCompass();
		//debugCompass();
		//debugIMU();
		//debugHeading();
		digitalWrite(13, abs(ypr[PITCH]) < 1 && abs(ypr[ROLL]) < 1 ? HIGH : LOW);
		//Serial.print("Yaw: ");
		//Serial.print(map(ypr[YAW], -180, 180, 360, 0));
		//Serial.print("\t\tCompass Heading: ");
		heading = tiltCompensateCompass(compass_data);
		Serial.println(heading);
		
		if (count % 100 == 99) {
			count = 0;
			Serial.print("Pitch: ");
			Serial.print(ypr[PITCH]);
			Serial.print("\t\tMapped Heading: ");
			Serial.print(yaw_map[map(ypr[YAW], -180, 180, 359, 0)]);
			Serial.println();
		}
		else {	count++;}
		
		if (abs(ypr[PITCH]) < 1 && abs(ypr[ROLL]) < 1) {
			int yaw_heading = map(ypr[YAW], -180, 180, 360, 0);
			for (int i = 0; i < 360; i++) {
				int index;
				if (yaw_heading + i < 360) {	index = yaw_heading + i;}
				else {	index = yaw_heading + i - 360;}
				
				int int_heading = int(heading);
				if (int_heading + i < 360) {	yaw_map[index] = int_heading + i;}
				else {	yaw_map[index] = int_heading + i - 360;}
				/*
				Serial.print("yaw_map[");
				Serial.print(index);
				Serial.print("] = ");
				Serial.println(yaw_map[index]);
				*/
			}
		}
	}
}

// Prints measured yaw, pitch, and roll to USB serial
void debugIMU() {
	Serial.print("Y: ");	Serial.print(ypr[YAW]);
	Serial.print("\tP: ");	Serial.print(ypr[PITCH]);
	Serial.print("\tR: ");	Serial.print(ypr[ROLL]);
	Serial.println();
}

// Prints compass data to USB serial
void debugCompass() {
	Serial.print("X: ");	Serial.print(compass_data[0]);
	Serial.print("\tY: ");	Serial.print(compass_data[1]);
	Serial.print("\tZ: ");	Serial.print(compass_data[2]);
	Serial.println();
}

// Prints just the heading
void debugHeading() {
    Serial.print("Heading: ");
	heading = tiltCompensateCompass(compass_data);
    Serial.print(heading);
    Serial.println();
}

// Prints comma separated value spreadhseet data
void printCSV() {
	float xyz[3];
	compass.getValues(xyz);
	for (int i = 0; i < 3; i++) {
		Serial.print(xyz[i]);
		Serial.print(", ");
	}
	
	Serial.print(compass_data[0]);
	Serial.print(", ");	Serial.print(compass_data[1]);
	Serial.print(", ");	Serial.print(compass_data[2]);
	Serial.print(", ");	Serial.print(xh);
	Serial.print(", ");	Serial.print(yh);
	Serial.println();
}
