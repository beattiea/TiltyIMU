// Settings file
//#include "settings.h"

// Wire library
#include <i2c_t3.h>

// IMU sensor libraries
#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"
// Instantiate the IMU
MPU6050 imu;

// Places to store MPU6050 IMU readings
float ypr[3];		   // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float ypr_offset[3];
// IMU angle array positions
#define YAW 0
#define PITCH 1
#define ROLL 2

void setup() {
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);
	delay(5);
	imu = MPU6050();
	imu.reset();
	delay(5);
	if (imu.init() == false) {	SOS(0);}
	
	setupDMP();
}

void loop() {
	
	readDMP();
	printYPR();
}



// Error codes
// 0 = IMU not detected or failed initialization (flashes "SOS": ...---...)
// 1 = initial IMU DMP memory load failed
// 2 = DMP configuration updates failed
void SOS(int error) {
	int LED = 13;
	pinMode(LED, OUTPUT);
	
	while (true) {
		if (Serial) {
			Serial.print("error code: ");
			Serial.println(error);
		}
		
		if (error) {
			for (int i = 0; i < error; i++) {
				digitalWrite(LED, HIGH);
				delay(250);
				digitalWrite(LED, LOW);
				delay(250);
			}
		}
		else {
			// S
			for (int i = 0; i < 3; i++) {
				digitalWrite(LED, HIGH);
				delay(250);
				digitalWrite(LED, LOW);
				delay(250);
			}
			// O
			for (int i = 0; i < 3; i++) {
				digitalWrite(LED, HIGH);
				delay(500);
				digitalWrite(LED, LOW);
				delay(500);
			}
			// S
			for (int i = 0; i < 3; i++) {
				digitalWrite(LED, HIGH);
				delay(250);
				digitalWrite(LED, LOW);
				delay(250);
			}
		}
		delay(2000);
	}
}