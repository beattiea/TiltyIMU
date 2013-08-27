#include <i2c_t3.h>

//rc signal include
#include <RCsignal.h>

// IMU includes
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Altimeter includes
#include <MPL3115A2.h>

// Compass includes
#include <HMC5883.h>

// SPI mem includes
#include <SpiFlash.h>
#include <SPI.h>

#include <PID.h>

// Sensors
MPU6050 imu;
MPL3115A2 alt;
HMC5883 magn;

// Memory
SpiFlash mem;

//RC Signal
RCsignal RCInput(2, readRC);

// Sensor variables
#define YAW_INDEX 0 // ypr[] data index
#define PITCH_INDEX 1 // ypr[] data index
#define ROLL_INDEX 2 // ypr[] data index
float ypr[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float yaw = 0;
float axyz[3]; // Real world reference acceleration minus gravity
float az_offset = 1.115;
int ix,iy,iz; // compass sensor raw values

float sensor_alt;
float altitude = 0;
float heading;

float maxAlt = 1;

volatile int throttle;


float fusedAlt;

float kP = 50;
float kI = 1;
float kD = 0.0;

float limiter;

PID altLimit(&fusedAlt, &limiter, kP, kI, kD);

#include "Servo.h"

Servo throttleOutput;

float altitudeOffset = 0;

void setup() {
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	delay(5);
	
	setupDMP();
	alt.init();
	alt.setOversampling(7);
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
                //mem.begin(10, 2);
                //mem.eraseChip();
		for (int i = 0; i < 1000; i++) {
			readDMP();
			if (Serial) {
				Serial.println("Zeroing. . .");
			}
		}
	#endif
	
	while (!alt.getDataReady()) {}
	altitude = alt.readAltitudeM();
	
	//imu.setZAccelOffset(771);

        throttleOutput.attach(23);
        throttleOutput.writeMicroseconds(1000);
}

bool save = false;

bool altSet = false;

void loop(){
  
        if(throttle > 1100 && !altSet)
        {
          altitudeOffset = altitude;
          altSet = true;
        }
        else if(throttle < 1100 && altSet)
        {
          altitudeOffset = 0;
          altSet = false;
        }
        
	readDMP();
	computeAltitude();

        fusedAlt = altitude - altitudeOffset;
        
        altLimit.setInputTriggers (-2000000, maxAlt);

        if(altitude - altitudeOffset > maxAlt && altSet)
        {
          //altLimit.setLimits(0, throttle - 1150);
          altLimit.update();
          
          if (throttle - limiter > 1150) { throttleOutput.writeMicroseconds(throttle - limiter);}
          else {throttleOutput.writeMicroseconds(1150);}
          Serial.print("Limited: ");
          Serial.println(limiter);
        }
        else
        {
          altLimit.reset();
          throttleOutput.writeMicroseconds(throttle);
          Serial.println(throttle);
        }
        Serial.println(fusedAlt);
        //Serial.println(axyz[2]);
}

void readRC()
{
 throttle = RCInput.read(); 
}
