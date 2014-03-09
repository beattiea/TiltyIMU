#include "DualMotorDriver.h"
#include "MPL3115A2.h"
#include "i2c_t3.h"

#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"

MPL3115A2 altimeter;
MPU6050 imu;

int loops;
int errors;
uint8_t speed;

// Places to store MPU6050 IMU readings
float ypr[3];		   // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float ypr_offset[3];
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	pinMode(13, OUTPUT);
	
	altimeter.init();
	imu = MPU6050();
	imu.reset();
	delay(5);
	setupDMP();
	
	setup1819();
	
	while (!Serial) {}
}

union data_union {
	uint8_t bytes[4];
	float float32;
	uint32_t long32;
} data_union;

void loop() {
	/*
	Serial.print("Altitude: ");
	Serial.println(altimeter.readAltitudeM());
	
	setup1617();
	//delayMicroseconds(10);
	Wire.beginTransmission(0x03);
	Wire.write(0x02);
	Wire.write(speed);
	Wire.write(speed - 256);
	Wire.endTransmission();
	
	delayMicroseconds(100);
	
	Wire.beginTransmission(0x03);
	Wire.write(0x08);
	Wire.endTransmission();
	
	delayMicroseconds(100);
	
	Wire.requestFrom(0x03, 4);
	data_union.bytes[0] = Wire.read();
	data_union.bytes[1] = Wire.read();
	data_union.bytes[2] = Wire.read();
	data_union.bytes[3] = Wire.read();
	Serial.print("Encoder: ");
	Serial.println(data_union.float32);
	Serial.print("Set speed: ");
	Serial.println(speed);
	*/
	/*
	Serial.print("Speed: ");
	uint8_t data = Wire.read();
	Serial.println(data);
	if (data != speed) {	
		errors++;
		Serial.print("				ERROR! Speed set to: ");
		Serial.println(speed);
	}
	*/
	/*
	speed++;
	
	setup1819();
	Serial.print("Time: ");
	Serial.println(micros() - start);
	//Serial.print("Errors: ");
	//Serial.println(errors);
	Serial.print("Loops: ");
	Serial.println(loops);
	Serial.println();
	
	loops++;
	delay(25);
	*/
	if (imu.getIntDataReadyStatus()) {
		readDMP();
		Serial.println(ypr[1]);
	}
	
	long start = micros();
	
	setup1617();
	
	uint8_t data1, data2;
	data1 = (int(ypr[1]) * 2) >> 8;
	data2 = (int(ypr[1]) * 2) & 0xFF;
	
	Wire.beginTransmission(0x03);
	Wire.write(0x08);
	Wire.write(data1);
	Wire.write(data2);
	if (Wire.endTransmission()) {errors++;}
	
	Serial.print("Speed: "); Serial.println((int(ypr[1]) * 2));
	
	delayMicroseconds(200);
	
	Wire.beginTransmission(0x03);
	Wire.write(0x08);
	if (Wire.endTransmission()) {errors++;}
	
	delayMicroseconds(50);
	
	Wire.requestFrom(0x03, 4);
	data_union.bytes[0] = Wire.read();
	data_union.bytes[1] = Wire.read();
	data_union.bytes[2] = Wire.read();
	data_union.bytes[3] = Wire.read();
	
	Serial.print("Encoder Rate: "); Serial.println(data_union.float32);
	
	Serial.print("Loop Time: "); Serial.println(micros() - start);
	
	Serial.print("Error rate: "); Serial.print((float(errors) / loops) * 100, 4); Serial.println(char(37));
	Serial.println();
	
	setup1819();
	
	//delay(5);
	loops++;

}

void setupOne() {
    *portModeRegister(16) = 0; // input
    CORE_PIN16_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(17) = 0; // input
    CORE_PIN17_CONFIG = PORT_PCR_MUX(1);
}

void setup1617() {
    CORE_PIN16_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN17_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
}

void setup1819() {
    CORE_PIN18_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN19_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(16) = 0; // input
    CORE_PIN16_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(17) = 0; // input
    CORE_PIN17_CONFIG = PORT_PCR_MUX(1);
}

void setupBoth() {
    CORE_PIN18_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN19_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
	
    CORE_PIN16_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN17_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
}

void scanAll() {
	setup1617();
	Serial.println("I2C Devices on 5v Line:");
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}	
	Serial.println();

	Serial.println("I2C Devices on 3v3 line:");
	setup1819();
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}
}