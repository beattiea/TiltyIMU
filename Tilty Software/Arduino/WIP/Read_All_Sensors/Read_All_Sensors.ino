#include <i2c_t3.h>
#include <HMC5883.h>
#include <MPL3115A2.h>

#include <I2Cdev.h>
#include <MPU6050.h>
#include <EEPROM.h>

//#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
//#include <Wire.h> // Uncomment to use standard Wire library on normal Arduinos
#include <i2c_t3.h> // Uncomment to use I2C_t3 Wire library on Teensy 3.0
#include <SPI.h>

// Compass variables
int compass_x, compass_y, compass_z;
int mapped_x, mapped_y, mapped_z;
float heading_x, heading_y;
int compass_x_min = 1000, compass_x_max = -1000;
int compass_y_min = 1000, compass_y_max = -1000;
int compass_z_min = 1000, compass_z_max = -1000;

// IMU variables
int raw_values[9];
float ypr[3]; // yaw pitch roll
float val[9];

//instantiate the compass 
HMC5883 compass  = HMC5883();

//instantiate the IMU
FreeIMU my3IMU = FreeIMU();

//instantiate the compass
MPL3115A2 altimeter;

void setup()
{
	//Open up some serial communications with the computer
	Serial.begin(115200);
	
	//Start the internal I2C Bus for the sensors 
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	
	my3IMU.init();
	compass.init(0);
	altimeter.init();	
}

void loop()
{
	compass.getValues(&compass_x, &compass_y, &compass_z);
	
	if (compass_x < compass_x_min) {  compass_x_min = compass_x;}
	if (compass_x > compass_x_max) {  compass_x_max = compass_x;}
	if (compass_y < compass_y_min) {  compass_y_min = compass_y;}
	if (compass_y > compass_y_max) {  compass_y_max = compass_y;}
	if (compass_z < compass_z_min) {  compass_z_min = compass_z;}
	if (compass_z > compass_z_max) {  compass_z_max = compass_z;}
	
	mapped_x = map(compass_x, compass_x_min, compass_x_max, -360, 360);
	mapped_y = map(compass_y, compass_y_min, compass_y_max, -360, 360);
	mapped_z = map(compass_z, compass_z_min, compass_z_max, -360, 360);
	/*
	Serial.print(compass_x); Serial.print("\t");
	Serial.print(compass_x_min); Serial.print("\t");
	Serial.print(compass_x_max); Serial.print("\t\t");
	Serial.print(compass_y); Serial.print("\t");
	Serial.print(compass_y_min); Serial.print("\t");
	Serial.print(compass_y_max); Serial.print("\t");
	*/
	//heading_x = mapped_x * cos(ypr[1] * M_PI / 180) + mapped_z * sin(ypr[1] * M_PI / 180);
	//heading_y = mapped_x * sin(ypr[2] * M_PI / 180) + mapped_y * cos(ypr[2] * M_PI / 180) - mapped_z * sin(ypr[2] * M_PI / 180) * cos(ypr[1] * M_PI / 180);
	
	heading_x = compass_x * cos(ypr[1] * M_PI / 180) + compass_z * sin(ypr[1] * M_PI / 180);
	heading_y = compass_x * sin(ypr[2] * M_PI / 180) + compass_y * cos(ypr[2] * M_PI / 180) - compass_z * sin(ypr[2] * M_PI / 180) * cos(ypr[1] * M_PI / 180);
	
	Serial.print(" Heading: ");
	float heading = atan2(compass_y, compass_x);
	if(heading < 0) {
		heading += 2 * M_PI;
	}
	Serial.print(heading * 180/M_PI);
	
	my3IMU.getYawPitchRoll(ypr);
	Serial.print("\t\tYaw: ");
	Serial.print(ypr[0]);
	Serial.print(" Pitch: ");
	Serial.print(ypr[1]);
	Serial.print(" Roll: ");
	Serial.print(ypr[2]);
	
	Serial.print("\t\t Altitude: "); Serial.print(altimeter.readAltitudeM());
	Serial.print("\t\t Temperature: "); Serial.println(altimeter.readTempC());
}
