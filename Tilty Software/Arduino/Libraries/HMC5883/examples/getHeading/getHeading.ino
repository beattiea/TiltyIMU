#include <i2c_t3.h>
#include <HMC5883.h>

HMC5883 magn;

int x,y,z; // compass sensor raw values
// X, Y, and Z max and min readings, used to calibrate offsets from zero for a non-ideal environment
int16_t x_min = 0, x_max = 0;
int16_t y_min = 0, y_max = 0;
int16_t z_min = 0, z_max = 0;

float heading;// Heading calculated with compass data

void setup(void) {
	Serial.begin(9600);
	Wire.begin();

	magn.init();// returns true if device is successfully recognized
}

void loop() { 
	// Get values as ints, only when new data is available
	if (magn.getDataReady()) {
		
		magn.getRaw(&x, &y, &z);
		
		checkOffsets();
		
		Serial1.print("Heading: ");
		Serial1.println(magn.getHeading(x, y));
	}
}

void checkOffsets() {
	// Check for new minimums
	if (x < x_min) {	x_min = x;}
	if (y < y_min) {	y_min = y;}
	if (z < z_min) {	z_min = z;}
	
	// Check for new maximums
	if (x > x_max) {	x_max = x;}
	if (y > y_max) {	y_max = y;}
	if (z > z_max) {	z_max = z;}
	
	x -= (x_min + x_max) / 2;
	y -= (y_min + y_max) / 2;
	z -= (z_min + z_max) / 2;
}