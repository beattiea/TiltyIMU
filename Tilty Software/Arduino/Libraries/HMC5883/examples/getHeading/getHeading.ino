#include <i2c_t3.h>
#include <HMC5883.h>

HMC5883 magn;

int x,y,z; // compass sensor raw values
// X, Y, and Z max and min readings, used to calibrate offsets from zero for a non-ideal environment
int16_t x_min = -1836, x_max = 738;
int16_t y_min = -1399, y_max = 1227;
int16_t z_min = -1031, z_max = 1404;

void setup(void) {
	Serial.begin(9600);
	Wire.begin();

	magn.init();// returns true if device is successfully recognized
}

void loop() { 
	float heading;
	
	// Get values as ints, only when new data is available
	if (magn.getDataReady()) {
		
		magn.getRaw(&x, &y, &z);
		
		x -= (x_min + x_max) / 2;
		y -= (y_min + y_max) / 2;
		z -= (z_min + z_max) / 2;
		
		Serial.print("Heading: ");
		Serial.println(magn.getHeading(x, y));
	}
}