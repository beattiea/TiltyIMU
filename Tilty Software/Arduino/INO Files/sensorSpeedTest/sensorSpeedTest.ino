#include <i2c_t3.h>
#include <HMC5883.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <MPL3115A2.h>

//Places to store the compass reading
int compass_x, compass_y, compass_z;

//Places to store MPU6050 readings
int16_t ax, ay, az;
int16_t gx, gy, gz;

//instantiate a compass 
HMC5883 compass;

//instantiate the IMU
MPU6050 imu;

MPL3115A2 altimeter;

void setup()
{
	//Open up some serial communications with the computer
	Serial.begin(115200);
	
	//Start the internal I2C Bus for the sensors 
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_1500);
	
	delay(10);
	
	imu = MPU6050();
	imu.initialize();
	imu.setI2CBypassEnabled(true);

	delay(10);
	
	//construct the compass
	compass = HMC5883();
	
	//initialize the compass
	compass.init(0);
	
	altimeter.init();
}

long start, stop;

void loop()
{
	Serial.println("Testing raw reading speed (average on 1024 samples):");
	start = micros();
	for(int i=0; i<1024; i++) {
		compass.getValues(&compass_x, &compass_y, &compass_z);
		imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		if (altimeter.checkData()) {
			  altimeter.readAltitudeM();
			  altimeter.readTempC();
		}
	}
	stop = micros();
	Serial.print("--> result: ");
	Serial.print((stop - start) / 1024);
	Serial.print(" microseconds .... ");
	Serial.print(((stop - start) / 1024) / 1000.0);
	Serial.println(" milliseconds\n");

	Serial.print("Compass x: "); Serial.print(compass_x);
	Serial.print(" y: "); Serial.print(compass_y);
	Serial.print(" z: "); Serial.print(compass_z);
	
	Serial.print("\t\tAccelerometer x: "); Serial.print(ax);
	Serial.print(" y: "); Serial.print(ay);
	Serial.print(" z: "); Serial.print(az);
	
	Serial.print("\t\tGyro x: "); Serial.print(gx);
	Serial.print(" y: "); Serial.print(gy);
	Serial.print(" z: "); Serial.print(gz);
	
	Serial.print("\t\t Altitude: "); Serial.print(altimeter.readAltitudeM());
	Serial.print("\t\t Temperature: "); Serial.println(altimeter.readTempC());
}
