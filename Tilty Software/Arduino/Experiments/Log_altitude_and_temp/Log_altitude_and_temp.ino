#include <i2c_t3.h>
#include <MPL3115A2.h>

#include <SpiFlash.h>
#include <SPI.h>


MPL3115A2 altimeter;
SpiFlash flash;

void setup() {
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);//  Starts I2C on Teensy
	Serial.begin(115200);
	delay(5);
	
	altimeter.init();
	delay(5);
	altimeter.setOversampling(7);// Sets oversampling to 2^n (0-7)
	
	flash.begin(10, 2);
	
	Serial.println("Erasing memory. . .");
	flash.eraseChip();
	
	while (Serial) {
		Serial.println("Waiting for a disconnect to begin logging. . .");
		delay(500);
	}
}

void loop() {
	while (!Serial) {
		flash.bufferData(altimeter.readAltitudeM());//  Use readAltitudeF() for feet
		flash.bufferData(altimeter.readTempC());//  Use readTempF() for fahrenheit
		
		while (!altimeter.getDataReady()) {  delay(1);}
	}
	
	while (Serial) {
		flash.writeBuffer(flash.getWrittenPages() * 256);
		delay(10);
		Serial.println("Altitude, Temperature");
		for (int i = 0; i < flash.getWrittenPages() * 256; i += 8) {
			Serial.print(flash.readFloat(i));
			Serial.print(", ");
			Serial.println(flash.readFloat(i + 4));
		}
		
		flash.eraseChip();
		while (Serial) {}
	}
}