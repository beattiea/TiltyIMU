#include <TiltyIMU.h>

#include <i2c_t3.h>
#include <FastServo.h> // Uncomment this line to use Fast Servo library
//#include <Servo.h> // Uncomment this line to use standard Servo library

#include <I2Cdev.h>
#define INCLUDE_DMP

TiltyIMU tilty;

int int_data[3];
int16_t int16_data[3];
float float_data[3];
float alt;

int16_t x_offset = -4600;
int16_t y_offset = 709;
int16_t z_offset = 771;

void setup() {
	while (!Serial) {}
	
	tilty.init();

	x_offset = tilty.imu.getXAccelOffset();
	y_offset = tilty.imu.getYAccelOffset();
	z_offset = tilty.imu.getZAccelOffset();
	
	tilty.imu.setZAccelOffset(771);
	
	Serial.print("X Accel Offset Register: ");
	Serial.println(tilty.imu.getXAccelOffset());
	
	Serial.print("Y Accel Offset Register: ");
	Serial.println(tilty.imu.getYAccelOffset());
	
	Serial.print("Z Accel Offset Register: ");
	Serial.println(tilty.imu.getZAccelOffset());
}

long start;

void loop() {
	//start = micros();
	tilty.updateSensors();
	//tilty.readAltitude(&alt);
	if (tilty.imu_updated) {
		tilty.readNormalAccelerations(float_data);
		tilty.readAngles(float_data);
		
		Serial.print(float_data[0]);
		Serial.print("\t\t");
		Serial.print(float_data[1]);
		Serial.print("\t\t");
		Serial.println(float_data[2]);
	}
	//tilty.readAngles(float_data);
	//tilty.getAccel(int_data);
	
	//Serial.println(micros() - start);
	
	//tilty.updateSensors();
	
	//tilty.alt.readAltitudeM(&float_data[0]);
	//Serial.println(float_data[0]);
	
	/*
	Serial.print(int_data[0]);
	Serial.print("\t\t");
	Serial.print(int_data[1]);
	Serial.print("\t\t");
	Serial.println(int_data[2]);
	*/
	
	if (!Serial.available()) {
		/*
		Serial.print("X Accel Offset Register: ");
		Serial.println(tilty.imu.getXAccelOffset());
		if (float_data[0] > 0) {
			x_offset += 1;
			tilty.imu.setXAccelOffset(x_offset);
		}
		else if (float_data[0] < 0) {
			x_offset -= 1;
			tilty.imu.setXAccelOffset(x_offset);
		}
		
		Serial.print("Y Accel Offset Register: ");
		Serial.println(tilty.imu.getYAccelOffset());
		if (float_data[1] > 0) {
			y_offset += 1;
			tilty.imu.setYAccelOffset(y_offset);
		}
		else if (float_data[1] < 0) {
			y_offset -= 1;
			tilty.imu.setYAccelOffset(y_offset);
		}
		
		
		Serial.print("Z Accel Offset Register: ");
		Serial.println(tilty.imu.getZAccelOffset());
		if (float_data[2] > 0) {
			z_offset += 1;
			tilty.imu.setZAccelOffset(z_offset);
		}
		else if (float_data[2] < 0) {
			z_offset -= 1;
			tilty.imu.setZAccelOffset(z_offset);
		}
		*/
	}
	
	
	
	/*
	tilty.getGyroRates(ypr);
	
	Serial.print(ypr[0]);
	Serial.print("\t\t");
	Serial.print(ypr[1]);
	Serial.print("\t\t");
	Serial.println(ypr[2]);
	*/
	
	//Serial.println(tilty.readAltitude(&alt));
}