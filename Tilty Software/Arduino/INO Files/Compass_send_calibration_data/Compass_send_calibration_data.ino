#include <i2c_t3.h>
#include <HMC5883.h>

HMC5883 magn;

void setup(void) {
	Serial.begin(115200);
	Wire.begin();

	magn.init();// returns true if device is successfully recognized
	magn.setGain(7);
}

void loop() { 
	int ix,iy,iz;
	
	// Get values as ints, only when new data is available
	if (magn.getDataReady()) {
		if (Serial.available()) {
			if (Serial.read() == 0x22) {
				magn.getRaw(&ix,&iy,&iz);
				Serial.write(ix & 0xFF);
				Serial.write(ix >> 8);
				Serial.write(iy & 0xFF);
				Serial.write(iy >> 8);
				Serial.write(iz & 0xFF);
				Serial.write(iy >> 8);
				Serial.write(10);
			}
		}
	}
}