#include <FastServo.h>
#include <PID.h>

#include <i2c_t3.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"


MPU6050 mpu;
Servo roll, pitch, yaw, throttle;

float ypr[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

#define ROLL_PIN 2 // Servo header 1
#define ROLL_INDEX 2 // ypr[] data index
float roll_kP = 10;
float roll_kI = 1;
float roll_kD = 0.025;
float roll_servo = 1500;
PID roll_pid = PID(&ypr[ROLL_INDEX], &roll_servo, roll_kP, roll_kI, roll_kD, 1);

#define PITCH_INDEX 1;
#define YAW_INDEX 0;

#define PITCH_PIN 3 // Servo header 2
#define YAW_PIN 23 // Servo header 4
#define THROTTLE_PIN 22 // Servo header 3

void setup() {
	Serial.begin(115200);
	
	roll.attach(ROLL_PIN);
	roll_pid.setLimits(-500, 500); // Sets servo output limits for PID
	
	pitch.attach(PITCH_PIN);
	
	//Wire.begin();
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	delay(5);
	
	while (!Serial) {}
	
	setupDMP();
}

void loop() {
	readDMP();
	roll_pid.update();
	Serial.println(roll_servo);
}