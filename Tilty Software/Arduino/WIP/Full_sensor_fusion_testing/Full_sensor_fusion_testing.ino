#include <i2c_t3.h>

// IMU includes
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Altimeter includes
#include <MPL3115A2.h>

// Compass includes
#include <HMC5883.h>

// Sensor constructors
MPU6050 imu;
MPL3115A2 alt;
HMC5883 magn;

// Sensor variables
#define YAW_INDEX 0 // ypr[] data index
#define PITCH_INDEX 1 // ypr[] data index
#define ROLL_INDEX 2 // ypr[] data index
float ypr[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float yaw = 0;
float axyz[3]; // Real world reference acceleration minus gravity
int ix,iy,iz; // compass sensor raw values

float altitude;


void setup() {
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	delay(5);
	
	setupDMP();
	alt.init();
	alt.setOversampling(0);
	magn.init();
	
	#ifdef USE_BT
		Serial1.begin(115200);
		#define myPort Serial1
		//while (!myPort.available()) {	readDMP();}
		for (int i = 0; i < 1000; i++) {
			readDMP();
		}
		while (myPort.available()) {	myPort.read();}
	#else
		Serial.begin(115200);
		#define myPort Serial
		//while (!myPort) {	readDMP();}
		for (int i = 0; i < 1000; i++) {
			readDMP();
		}
	#endif
}

void loop() {
	readDMP();
	computeAltitude();
	calculateYaw();
}