#include <i2c_t3.h>
#include <HMC5883.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#define myPort Serial2
#define port Serial

HMC5883 magn;
MPU6050 imu;

#define YAW_INDEX 0 // ypr[] data index
#define PITCH_INDEX 1 // ypr[] data index
#define ROLL_INDEX 2 // ypr[] data index
float ypr[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

int x,y,z; // compass sensor raw values
// X, Y, and Z max and min readings, used to calibrate offsets from zero for a non-ideal environment
int16_t x_min = 1000, x_max = 0;
int16_t y_min = 1000, y_max = 0;
int16_t z_min = 1000, z_max = 0;

float heading;// Heading calculated with compass data

void setup(void) {
	port.begin(115200);
	Wire.begin();

	magn.init();// returns true if device is successfully recognized
	//setupDMP();
	
	//magn.setGain(0);
}

void loop() { 
	// Get values as ints, only when new data is available
	//readDMP();
	if (magn.getDataReady()) {
		
		magn.getRaw(&x, &y, &z);
		
		checkOffsets();
		
		/*
		port.print("C");
		port.println(magn.getTiltCompensatedHeading(x, y, z, ypr[PITCH_INDEX], ypr[ROLL_INDEX]));
		port.print("Y");
		port.println(ypr[YAW_INDEX]);
		*/
		
		port.print("X");
		port.println(float(x));
		port.print("Y");
		port.println(float(y));
		port.print("Z");
		port.println(float(z));
	}
	delay(75);
}

void checkOffsets() {
	// Check for new minimums
	if (x < x_min) {	x_min = x;}
	if (y < y_min) {	y_min = y;}
	if (z < z_min) {	z_min = z;}
	
	// Check for new maximums
	if (x > x_max) {	x_max = x;}
	if (y > y_max) {	y_max = y;}
	if (z > z_max) {	z_max = z;}
	
	// Check for errors
	if (x_min == -4096) {	x_min = 1000;}
	if (y_min == -4096) {	y_min = 1000;}
	if (z_min == -4096) {	z_min = 1000;}
	
	if (x_max == -4096) {	x_max = 0;}
	if (y_max == -4096) {	y_max = 0;}
	if (z_max == -4096) {	z_max = 0;}
	
	//x -= (x_min + x_max) / 2;
	//y -= (y_min + y_max) / 2;
	//z -= (z_min + z_max) / 2;
	/*
	Serial.print("X: ");
	Serial.print(x_min);
	Serial.print(", ");
	Serial.print(x_max);
	Serial.print(", ");
	Serial.println(x);
	
	Serial.print("Y: ");
	Serial.print(y_min);
	Serial.print(", ");
	Serial.print(y_max);
	Serial.print(", ");
	Serial.println(y);
	
	Serial.print("Z: ");
	Serial.print(z_min);
	Serial.print(", ");
	Serial.print(z_max);
	Serial.print(", ");
	Serial.println(y);
	*/
	/*
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.print(", ");
	Serial.println(z);
	*/
}