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

bool compass_avail, imu_avail, alt_avail, flash_avail, bt_avail; // variabless to indicate whether sensor is available

// Constant variable #defines
#define VOLTAGE_SENSE_PIN 14
#define VOLTAGE_DIVIDER 0.05061465
#define SS_PIN 6
#define BT_COMMAND 15
#define BT_DEFAULT_BAUD 38400
#define TILTY_DEFAULT_BT_BAUD 115200

void setup()
{
	//Open up some serial communications with the computer
	Serial.begin(115200);
	pinMode(BT_COMMAND, OUTPUT);
	digitalWrite(BT_COMMAND, HIGH);
	
	flash.begin(SS_PIN, 2);
	
	while (!Serial) {}
	
	//Start the internal I2C Bus for the sensors 
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_800);
	
	delay(10);
	
	// initialize the IMU
	imu = MPU6050();
	imu_avail = imu.init();
	Serial.print("IMU status...\t\t\t");
	Serial.println(imu_avail ? "OK!" : "NOT OK!");
	
	// initialize the compass
	compass_avail = compass.init();
	Serial.print("Compass status...\t\t");
	Serial.println(compass_avail ? "OK!" : "NOT OK!");
	
	// initialize the altimeter and set oversampling to 0 to speed up measurements
	alt_avail = altimeter.init();
	if (alt_avail) {	altimeter.setOversampling(0);}
	Serial.print("Altimeter status...\t\t");
	Serial.println(alt_avail ? "OK!" : "NOT OK!");

	// initialize and check for the flash memory chip
	flash_avail = flash.getManufacturer() == 1 ? true : false;
	Serial.print("Flash memory status...\t\t");
	Serial.println(flash_avail ? "OK!" : "NOT OK!");
	
	// initialize and check for the bluetooth chip
	int baud = findBaud();
	Serial1.begin(baud);
	bt_avail = checkBTok();
	Serial.print("Bluetooth status...\t\t");
	Serial.println(bt_avail ? "OK!" : "NOT OK!\n");
	if (bt_avail) {
		Serial.print("\tBluetooth version: ");
		getBTversion();
		Serial.print("\tSet bluetooth name to TiltyBT: ");
		setBTname();
		setBTbaud();
		Serial.print("\tBluetooth baud set to: ");
		Serial.println(findBaud());
		
		Serial.println();
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




bool checkBTok() {
	elapsedMillis timer;
	char ok[4] = {'O', 'K', '\r', '\n'};
	
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT\r\n");
	delayMicroseconds(25);
	
	digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);
	
	while (Serial1.available() < sizeof(ok) && timer < 250) {}
	for (int i = 0; i < sizeof(ok); i++) {
		if (Serial1.read() != ok[i]) {	return false;}
	}
	return true;
}

bool getBTversion() {
	elapsedMillis timer;
	char version[9] = {'+', 'V', 'E', 'R', 'S', 'I', 'O', 'N', ':'};
	
	Serial1.begin(BT_DEFAULT_BAUD);
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT+VERSION?\r\n");
	delayMicroseconds(25);
	
	digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);
	
	while (Serial1.available() < sizeof(version) && timer < 250) {}

	while (Serial1.available()) {
		for (int i = 0; i < 9; i++) {
			Serial1.read();
		}
		while (Serial1.available()) {
			char data = Serial1.read();
			if (data != 'O' && data != 'K' && data != '\n' && data != '\r') {	Serial.print(data);}
			delay(1);
		}
	}
	Serial.println();
}

bool setBTbaud() {
	elapsedMillis timer;
	char ok[4] = {'O', 'K', '\r', '\n'};
	
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT+UART=");
	Serial1.print(TILTY_DEFAULT_BT_BAUD);
	Serial1.print(",0,0\r\n");
	delayMicroseconds(25);
	
	digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);

	while (Serial1.available() < sizeof(ok) && timer < 250) {}
	for (int i = 0; i < sizeof(ok); i++) {
		if (Serial1.read() != ok[i]) {	return false;}
	}
	
	digitalWrite(BT_COMMAND, HIGH);
	delayMicroseconds(10);
	
	Serial1.print("AT+RESET\r\n");
	delayMicroseconds(25);
	
	digitalWrite(BT_COMMAND, LOW);
	delayMicroseconds(10);
	
	Serial1.end();
	delay(25);
	Serial1.begin(TILTY_DEFAULT_BT_BAUD);
	delay(1000);
	
	int baud = findBaud();
	if (baud == 115200) {	return true;}
	else {	return false;}
}

bool setBTname() {
	elapsedMillis timer;
	
	digitalWrite(BT_COMMAND, HIGH);
	delay(10);
	
	Serial1.print("AT+NAME=TiltyBT\r\n");
	delay(25);
	
	digitalWrite(BT_COMMAND, LOW);
	delay(10);

	delay(25);
	while (Serial1.available()) {
		Serial.print((char)Serial1.read());
	}
}


int _bauds[] = {9600, 38400, 57600, 115200, 230400, 460800};
int findBaud()
{
  for (int i = 0; i < sizeof(_bauds) / 4; i++)
  {
	digitalWrite(BT_COMMAND, HIGH);
	Serial1.begin(_bauds[i]);
	delay(100);
	Serial1.write("AT\r\n");
	delay(100);
	digitalWrite(BT_COMMAND, LOW);

	if (Serial1.available()) 
	{
	  while (Serial1.available())//	 Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
	  {	Serial1.read();}
	  return _bauds[i];//  return the correct baud rate
	}
	Serial1.end();
  }
  return -1;
}
