#include <i2c_t3.h>
#include <HMC5883.h>
#include <MPL3115A2.h>

#include <I2Cdev.h>
#include <MPU6050.h>

//#include <Wire.h> // Uncomment to use standard Wire library on normal Arduinos
#include <i2c_t3.h> // Uncomment to use I2C_t3 Wire library on Teensy 3.0
#include <SPI.h>

#include <SpiFlash.h>

int raw_values[9];

// Places to store the compass reading
int compass_x, compass_y, compass_z;

// Places to store MPU6050 IMU readings
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Places to store altimeter readings
float altitude, temperature;

// Instantiate a compass 
HMC5883 compass;

// Instantiate the IMU
MPU6050 imu;

// Instantiate the altimeter
MPL3115A2 altimeter;

// Instantiate the flash memory
SpiFlash flash;

bool compass_avail, imu_avail, alt_avail; // variabless to indicate whether sensor is available

// Constant variable #defines
#define VOLTAGE_SENSE_PIN 14
#define VOLTAGE_DIVIDER 0.05061465
#define SS_PIN 6

void setup()
{
	//Open up some serial communications with the computer
	Serial.begin(115200);
	
	flash.begin(SS_PIN, 2);
	
	while (!Serial) {}
	
	//Start the internal I2C Bus for the sensors 
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);
	
	delay(10);
	
	// initialize the IMU
	imu = MPU6050();
	imu_avail = imu.init();
	if (imu_avail) {
		imu.setI2CBypassEnabled(true);
		Serial.println("IMU detected!");
	}
	else {
		Serial.println("IMU NOT detected!");
	}
	
	// initialize the compass
	compass_avail = compass.init();
	if (compass_avail) {
		Serial.println("COMPASS detected!");
	}
	else {
		Serial.println("COMPASS NOT detected!");
	}
	
	// initialize the altimeter and set oversampling to 0 to speed up measurements
	alt_avail = altimeter.init();
	if (alt_avail) {
		altimeter.setOversampling(0);
		Serial.println("ALTIMETER detected!");
	}
	else {
		altimeter.setOversampling(0);
		Serial.println("ALTIMETER NOT detected!");
	}

	if (flash.getManufacturer() == 1) {
		Serial.println("Flash chip detected!");
	}
	else {
		Serial.println("Flash chip not detected!");
	}
	
	Serial.println("Enter any character to continue...");
	
	while (!Serial.available()) {}
	while (Serial.available()) { Serial.read();}
}

void loop()
{
	if (compass_avail) {	compass.getValues(&compass_x, &compass_y, &compass_z);}
	if (imu_avail) { imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);}
	if (alt_avail) {
		altitude = altimeter.readAltitudeM();
		temperature = altimeter.readTempC();
		altimeter.forceMeasurement();
	}

	Serial.print("Compass x: "); Serial.print(compass_avail ? compass_x : 0);
	Serial.print(" y: "); Serial.print(compass_avail ? compass_y : 0);
	Serial.print(" z: "); Serial.print(compass_avail ? compass_z : 0);
	
	Serial.print("\t\tAccelerometer x: "); Serial.print(imu_avail ? ax : 0);
	Serial.print(" y: "); Serial.print(imu_avail ? ay : 0);
	Serial.print(" z: "); Serial.print(imu_avail ? az : 0);
	
	Serial.print("\t\tGyro x: "); Serial.print(imu_avail ? gx : 0);
	Serial.print(" y: "); Serial.print(imu_avail ? gx : 0);
	Serial.print(" z: "); Serial.print(imu_avail ? gx : 0);
	
	Serial.print("\t\t Altitude: "); Serial.print(alt_avail ? altitude : 0);
	Serial.print("\t\t Temperature: "); Serial.print(alt_avail ? temperature : 0);
	
	Serial.print("\t\t Voltage: "); Serial.print(analogRead(VOLTAGE_SENSE_PIN) * VOLTAGE_DIVIDER);
	
	Serial.println();
	
	// wait for all three sensors to have new data available
	if (imu_avail) { while (!imu.getIntDataReadyStatus());}
	if (compass_avail) { while (!compass.getDataReady());}
	if (alt_avail) { while (!altimeter.getDataReady());}
}
