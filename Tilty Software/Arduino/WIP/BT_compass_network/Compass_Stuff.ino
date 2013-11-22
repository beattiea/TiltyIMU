float compass_min[3] = {1024, 1024, 1024};
float compass_max[3] = {-1024, -1024, -1024};
float compass_minimum = 1024;
float compass_maximum = -1024;

float x_sf = 1;
float y_sf = 1;
float z_sf = 1;
float x_off = 0;
float y_off = 0;
float z_off = 0;

// Compensates for compass tilt using the IMU pitch and roll
float tiltCompensateCompass(float *xyz) {
	for (int i = 0; i < 3; i++) {
		ypr_radians[i] = ypr[i] * M_PI / 180;
	}
	
	xh = xyz[0] * cos(ypr_radians[PITCH]) + xyz[1] * sin(ypr_radians[PITCH]) * sin(ypr_radians[ROLL]) - xyz[2] * cos(ypr_radians[ROLL]) * sin(ypr_radians[PITCH]);// + x_off;
	yh = xyz[1] * cos(ypr_radians[ROLL]) + xyz[2] * sin(ypr_radians[ROLL]);// + y_off;
        
	if (xh < 0) {	return 180 - atan(yh / xh) * 180/M_PI;}
	if (xh > 0 && yh < 0) {	return -atan(yh / xh) * 180 / M_PI;}
	if (xh > 0 && yh > 0) {	return 360 - atan(yh / xh) * 180 / M_PI;}
}

// Calibrates for compass offsets and reading error
void calibrateCompass() {
	// check if new min or max value for all three axis
	for (int i = 0; i < 3; i++) {
		if (compass_data[i] < compass_min[i]) {	compass_min[i] = compass_data[i];}
		if (compass_data[i] > compass_max[i]) {	compass_max[i] = compass_data[i];}
	}
	calibrate();
}

void calibrate() {
	x_sf = (compass_max[1] - compass_min[1]) / (compass_max[0] - compass_min[0]);
	(1 > x_sf) ? x_sf = 1 : x_sf;
	
	y_sf = (compass_max[0] - compass_min[0]) / (compass_max[1] - compass_min[1]);
	(1 > y_sf) ? y_sf = 1 : y_sf;
	z_sf = (compass_max[0] - compass_min[0]) / (compass_max[2] - compass_min[2]);
	(1 > z_sf) ? z_sf = 1 : z_sf;
	
	x_off = ((compass_max[0] - compass_min[0]) / 2 - compass_max[0]) * x_sf;
	y_off = ((compass_max[1] - compass_min[1]) / 2 - compass_max[1]) * y_sf;
	z_off = ((compass_max[2] - compass_min[2]) / 2 - compass_max[2]) * z_sf;
	
	compass_data[0] = compass_data[0] * x_sf + x_off;
	compass_data[1] = compass_data[1] * y_sf + y_off;
	compass_data[2] = compass_data[2] * z_sf + z_off;
}