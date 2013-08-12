#include <Servo.h>
#include <PID.h>

#include <i2c_t3.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <HMC5883.h>

#define USE_BT // Uncomment to use Bluetooth instead of USB serial

MPU6050 imu;
HMC5883 compass;
Servo roll_servo, pitch_servo, yaw_servo, throttle_servo;

float ypr[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
int ix,iy,iz; // X, Y, and Z magnetometer values

#define ROLL_PIN 2 // Servo header 1
#define ROLL_INDEX 2 // ypr[] data index
float roll_offset = 0;
float roll_kP = 50;
float roll_kI = 200;
float roll_kD = 0.025;
float roll_value = 1500;
PID roll_pid = PID(&ypr[ROLL_INDEX], &roll_value, roll_kP, roll_kI, roll_kD, 0);

#define PITCH_PIN 3 // Servo header 2
#define PITCH_INDEX 1
float pitch_offset = 2.5;
float pitch_kP = 50;
float pitch_kI =100;
float pitch_kD = 0.05;
float pitch_value = 1500;
PID pitch_pid = PID(&ypr[PITCH_INDEX], &pitch_value, pitch_kP, pitch_kI, pitch_kD, 1);

#define YAW_PIN 22 // Servo header 3
#define YAW_INDEX 0
float yaw_kP = 0;
float yaw_kI = 0;
float yaw_kD = 5;
float yaw_value = 1500;
PID yaw_pid = PID(&ypr[YAW_INDEX], &yaw_value, yaw_kP, yaw_kI, yaw_kD, 1);

#define THROTTLE_PIN 23 // Servo header 4

void setup() {
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	delay(5);
	
	setupDMP();
	imu.setI2CBypassEnabled(true);
	
	compass.init();
	
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
	
	roll_servo.attach(ROLL_PIN); // Attach aileron servo to aileron servo header
	roll_pid.setLimits(-500, 500); // Sets servo output limits for PID
	roll_pid.setInputTriggers(-2, 2);
	pitch_servo.attach(PITCH_PIN); // Attach elevator servo to elevator servo header
	pitch_pid.setLimits(-500, 500); // Sets servo output limits for PID
	pitch_pid.setInputTriggers(0, 1.5);
	yaw_servo.attach(YAW_PIN); // Attach elevator servo to elevator servo header
	yaw_pid.setLimits(-250, 250); // Sets servo output limits for PID
}

void loop() {
	readDMP();
	
	compass.getValues(&ix, &iy, &iz);
	Serial.print(ix); Serial.print("\t\t"); Serial.print(iy);
	ix = map(ix, 347, 817, -130, 341);
	Serial.print("\t\t"); Serial.println(atan2(ix, iy) * 180/M_PI);
	
	roll_pid.update();
	pitch_pid.update();
	yaw_pid.update();
	
	roll_servo.writeMicroseconds(1500 + roll_value);
	pitch_servo.writeMicroseconds(1500 + pitch_value);
	yaw_servo.writeMicroseconds(1500 + yaw_value);
	
	myPort.print("Ailerons: ");
	myPort.print(roll_value);
	myPort.print("\tElevator: ");
	myPort.print(pitch_value);
	myPort.println();
	
	if (myPort.available()) {
		char data = myPort.read();
		Serial.println("Read Data. . .");
		if (data == '0') {
			Serial.println("Zeroed pitch and roll!");
			pitch_offset = ypr[PITCH_INDEX];
			roll_offset = ypr[ROLL_INDEX];
		}
		else if (data == 'r') {
			roll_pid.reset();
			pitch_pid.reset();
		}
		else if (data = 'p') {
			setP();
		}
		else if (data = 'i') {
			setI();
		}
		else if (data = 'd') {
			setD();
		}
	}
}