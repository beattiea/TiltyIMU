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

}

bool print = false;
float gyro_off, heading;
unsigned long count = 0;

void loop() {
	if (imu.getIntDataReadyStatus()) {
		readIMU();
                if (count % 6000 == 0) {
                    Serial.println(ypr[YAW]);
                }
                count++;
	}

	if (compass.getDataReady()) {
		compass.getValues(compass_data);
		calibrateCompass();
		//debugCompass();
		//debugIMU();
		//debugHeading();
	}
}

// Prints measured yaw, pitch, and roll to USB serial
void debugIMU() {
	Serial.print("Y: ");	Serial.print(ypr[0]);
	Serial.print("\tP: ");	Serial.print(ypr[1]);
	Serial.print("\tR: ");	Serial.print(ypr[2]);
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
