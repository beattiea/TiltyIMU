#include <i2c_t3.h> //	Uncomment for use on a Teensy 3.0

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 imu;

//byte readRegsiter(int reg_addr);

//#define PRINT_ST
//#define PRINT_FT
//#define PRINT_RAW
//#define PRINT_STR
#define PRINT_RES
//#define PRINT_PASSFAIL

int16_t ax_offset, ay_offset, az_offset, gx_offset, gy_offset, gz_offset;
int16_t ax, ay, az, gx, gy, gz;//	Self-test disabled sensor reading values
int16_t xa, ya, za, xg, yg, zg;//	Self-test enabled sensor values
int16_t xa_test, ya_test, za_test, xg_test, yg_test, zg_test;
int16_t ftax, ftay, ftaz, ftgx, ftgy, ftgz;//	Calculated factory trim values
int16_t stax, stay, staz, stgx, stgy, stgz;//	Calculated factory trim values
float dax, day, daz, dgx, dgy, dgz;//	Percent differences between Factory trim and self-test responses. Should be < 14% or 0.14.


void setup() {
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_1500);
	Serial.begin(115200);
	
	while (!Serial){};
	
	Serial.println("Initializing sensor...");
	imu.initialize();
	
	Serial.print("Testing device connections... ");
	if (imu.testConnection()) {
		Serial.println("MPU6050 connection successful");
	}
	else {
		Serial.println("MPU6050 connection failed");
		return;
	}
	
	Serial.print("Activating self-test mode... ");
	
	writeRegister(27, 0b11100000);
	writeRegister(28, 0b11110000);
	
	writeRegister(13, 0b00000000);
	writeRegister(14, 0b00000000);
	writeRegister(15, 0b11100000);
	writeRegister(16, 0b00000011);
	
	
	if (0b11100000 & readRegister(27) && 0b11110000 & readRegister(28)) {
		Serial.println("Activated");
	}
	else {
		Serial.println("Activation failed");
		return;
	}
	Serial.println("Send any character over serial to begin a new test...");
	while (!Serial.available()){}
	while (Serial.available()) {	Serial.read();}
}

void loop() {
	xa_test = ((readRegister(13) >> 3) & 0b00011100) | ((readRegister(16) >> 4) & 0b00000011);
	ya_test = ((readRegister(14) >> 3) & 0b00011100) | ((readRegister(16) >> 2) & 0b00000011);
	za_test = ((readRegister(15) >> 3) & 0b00011100) | ((readRegister(16) >> 0) & 0b00000011);
	xg_test = (readRegister(13) & 0b00011111);
	yg_test = (readRegister(14) & 0b00011111);
	zg_test = (readRegister(15) & 0b00011111);
	
	imu.getMotion6(&xa, &ya, &za, &xg, &yg, &zg);
	#ifdef PRINT_ST
		Serial.print("    Self-test data:\t");
		Serial.print(xa); Serial.print("\t");
		Serial.print(ya); Serial.print("\t");
		Serial.print(za); Serial.print("\t");
		Serial.print(xg); Serial.print("\t");
		Serial.print(yg); Serial.print("\t");
		Serial.println(zg);
	#endif
	
	
	
	if (xa_test != 0) {	ftax = 1392.64 * (pow(0.92, (xa_test - 1) / 30.0) / 0.34);}
	else {	ftax = 573;}
	if (ya_test != 0) {	ftay = 1392.64 * (pow(0.92, (ya_test - 1) / 30.0) / 0.34);}
	else {	ftay = 573;}
	if (za_test != 0) {	ftaz = 1392.64 * (pow(0.92, (za_test - 1) / 30.0) / 0.34);}
	else {	ftaz = 573;}
	if (xg_test != 0) {	ftgx = 3275 * pow(1.046, xg_test - 1);}
	else {	ftgx = 0;}
	if (yg_test != 0) {	ftgy = -3275 * pow(1.046, yg_test - 1);}
	else {	ftgy = 0;}
	if (zg_test != 0) {	ftgz = 3275 * pow(1.046, zg_test - 1);}
	else {	ftgz = 0;}
	
	#ifdef PRINT_FT
		Serial.print("    Fact trim data:\t");
		Serial.print(ftax); Serial.print("\t");
		Serial.print(ftay); Serial.print("\t");
		Serial.print(ftaz); Serial.print("\t");
		Serial.print(ftgx); Serial.print("\t");
		Serial.print(ftgy); Serial.print("\t");
		Serial.println(ftgz);
	#endif
	
	
	writeRegister(27, 0b00000000);
	writeRegister(28, 0b00010000);
	delay(5);
	
	
	
	imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	#ifdef PRINT_RAW
		Serial.print("          Raw data:\t");
		Serial.print(ax); Serial.print("\t");
		Serial.print(ay); Serial.print("\t");
		Serial.print(az); Serial.print("\t");
		Serial.print(gx); Serial.print("\t");
		Serial.print(gy); Serial.print("\t");
		Serial.println(gz);
		delay(5);
	#endif
	
	
	
	stax = xa - ax;
	stay = ya - ay;
	staz = za - az;
	stgx = xg - gx;
	stgy = yg - gy;
	stgz = zg - gz;
	
	#ifdef PRINT_STR
		Serial.print("Self-test Response:\t");
		Serial.print(stax); Serial.print("\t");
		Serial.print(stay); Serial.print("\t");
		Serial.print(staz); Serial.print("\t");
		Serial.print(stgx); Serial.print("\t");
		Serial.print(stgy); Serial.print("\t");
		Serial.println(stgz);
	#endif
	
	
	
	dax = (stax - ftax) / float(ftax);
	day = (stay- ftay) / float(ftay);
	daz = (staz - ftaz) / float(ftaz);
	dgx = (stgx - ftgx) / float(ftgx);
	dgy = (stgy - ftgy) / float(ftgy);
	dgz = (stgz - ftgz) / float(ftgz);
	
	#ifdef PRINT_RES
		Serial.print("           Results:\t");
		Serial.print(dax * 100, 0); Serial.print("%\t");
		Serial.print(day * 100, 0); Serial.print("%\t");
		Serial.print(daz * 100, 0); Serial.print("%\t");
		Serial.print(dgx * 100, 0); Serial.print("%\t");
		Serial.print(dgy * 100, 0); Serial.print("%\t");
		Serial.print(dgz * 100, 0); Serial.println("%");
	#endif
	
	
	
	#ifdef PRINT_PASSFAIL
		Serial.println(abs(dax) < 0.14 ? "Accel X:\tPASS" : "Accel X:\tFAIL");
		Serial.println(abs(day) < 0.14 ? "Accel Y:\tPASS" : "Accel Y:\tFAIL");
		Serial.println(abs(daz) < 0.14 ? "Accel Z:\tPASS" : "Accel Z:\tFAIL");
		Serial.println(abs(dgx) < 0.14 ? "Gyro X:\tPASS" : "Gyro X:\tFAIL");
		Serial.println(abs(dgy) < 0.14 ? "Gyro Y:\tPASS" : "Gyro Y:\tFAIL");
		Serial.println(abs(dgz) < 0.14 ? "Gyro Z:\tPASS" : "Gyro Z:\tFAIL");
	#endif
	
	writeRegister(27, 0b00000000);
	writeRegister(28, 0b00110000);
	delay(5);
	
	//Serial.println("\nSend any character over serial to begin a new test...");
	//while (!Serial.available()){}
	//while (Serial.available()) {	Serial.read();}
}

byte readRegister(int reg_addr)
{
	Wire.beginTransmission(MPU6050_DEFAULT_ADDRESS);
	Wire.write(reg_addr);
	Wire.endTransmission();
	
	Wire.requestFrom(MPU6050_DEFAULT_ADDRESS, 1);
	
	return Wire.read();
}

void writeRegister(int reg_addr, byte value) {
	Wire.beginTransmission(MPU6050_DEFAULT_ADDRESS);
	Wire.write(reg_addr);
	Wire.write(value);
	Wire.endTransmission();
}