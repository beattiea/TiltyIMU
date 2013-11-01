#include <i2c_t3.h>
#include <HMC5883.h>

HMC5883 magn;

void setup(void) {
	Serial.begin(9600);
	Wire.begin();

	magn.init();// returns true if device is successfully recognized
}

void loop() { 
	int ix,iy,iz;
	
	// Get values as ints, only when new data is available
	if (magn.getDataReady()) {
		magn.getRaw(&ix,&iy,&iz);
		Serial.print(ix);
		Serial.print(",");
		Serial.print(iy);
		Serial.print(",");
		Serial.println(iz);
	}
}