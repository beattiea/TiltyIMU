#include <i2c_t3.h>
#include <MPL3115A2.h>


MPL3115A2 altimeter;

void setup() {
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	Serial.begin(115200);
	delay(5);
	altimeter.init();
	while (!Serial) {}
}

void loop() {
	Serial.print("\nAltitude: ");
	Serial.print(altimeter.readAltitudeM());//  Use readAltitudeF() for feet
	Serial.println(" meters");
	
	Serial.print("Temperature: ");
	Serial.print(altimeter.readTempC());//  Use readTempF() for fahrenheit
	Serial.println(" degrees C");
	
	altimeter.forceMeasurement();// Forces the altimeter to immediately take another measurement and update all data
	
	while (!altimeter.getDataReady()) {  delay(1);}
}
	