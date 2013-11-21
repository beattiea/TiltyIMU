float compass_min[3] = {1024, 1024, 1024};
float compass_max[3] = {-1024, -1024, -1024};

// Compensates for compass tilt using the IMU pitch and roll
float tiltCompensateCompass(float *xyz) {
	for (int i = 0; i < 3; i++) {
		ypr_radians[i] = ypr[i] * M_PI / 180;
	}
	
        float xh = xyz[0] * cos(ypr_radians[PITCH]) + xyz[1] * sin(ypr_radians[PITCH]) * sin(ypr_radians[ROLL]) - xyz[2] * cos(ypr_radians[ROLL]) * sin(ypr_radians[PITCH]);
        float yh = xyz[1] * cos(ypr_radians[ROLL]) + xyz[2] * sin(ypr_radians[ROLL]);
        
	return atan(yh / xh) * 180/M_PI;
}

// Calibrates for compass offsets and reading error
void calibrateCompass() {
	// check if new min or max value for all three axis
	for (int i = 0; i < 3; i++) {
		if (compass_data[i] < compass_min[i]) {	compass_min[i] = compass_data[i];}
		if (compass_data[i] > compass_max[i]) {	compass_max[i] = compass_data[i];}
	}
	
	//	Compensate for error
	for (int i = 0; i < 3; i++) {
		compass_data[i] = map(compass_data[i], compass_min[i], compass_max[i], -360, 360);
	}
}
