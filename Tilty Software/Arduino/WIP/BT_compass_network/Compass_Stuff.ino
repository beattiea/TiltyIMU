float compass_min[3] = {1024, 1024, 1024};
float compass_max[3] = {-1024, -1024, -1024};
float compass_minimum = 1024;
float compass_maximum = -1024;

float h_min[2] = {1024, 1024};
float h_max[2] = {-1024, -1024};


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
		//xyz[i] = map(xyz[i], compass_min[i], compass_max[i], -314, 314);
	}
	
	//xh = xyz[0] * cos(ypr_radians[PITCH]) + xyz[1] * sin(ypr_radians[PITCH]) * sin(ypr_radians[ROLL]) + xyz[2] * cos(ypr_radians[ROLL]) * sin(ypr_radians[PITCH]);// + x_off;
	//yh = xyz[1] * cos(ypr_radians[ROLL]) - xyz[2] * sin(ypr_radians[ROLL]);// + y_off;
	
	//Testing version of tilt compensation, swapped x and y
	xh = xyz[1] * cos(ypr_radians[PITCH]) + xyz[0] * sin(ypr_radians[PITCH]) * sin(ypr_radians[ROLL]) + xyz[2] * cos(ypr_radians[ROLL]) * sin(ypr_radians[PITCH]);// + x_off;
	yh = xyz[0] * cos(ypr_radians[ROLL]) - xyz[2] * sin(ypr_radians[ROLL]);// + y_off;
	
	if (xh < h_min[0]) {	h_min[0] = xh;}
	if (yh < h_min[1]) {	h_min[1] = yh;}
	
	if (xh > h_max[0]) {	h_max[0] = xh;}
	if (yh > h_max[1]) {	h_max[1] = yh;}
	
	x_sf = (h_max[1] - h_min[1]) / (h_max[0] - h_min[0]);
	(1 > x_sf) ? x_sf = 1 : x_sf;
	y_sf = (h_max[0] - h_min[0]) / (h_max[1] - h_min[1]);
	(1 > y_sf) ? y_sf = 1 : y_sf;
	
	x_off = ((h_max[0] - h_min[0]) / 2 - h_max[0]) * x_sf;
	y_off = ((h_max[1] - h_min[1]) / 2 - h_max[1]) * y_sf;
	
	xh = xh * x_sf + x_off;
	yh = yh * y_sf + y_off;
	
	// Different compensation method, doesn't seem to work as well
	//xh = xyz[0] * cos(ypr_radians[PITCH]) + xyz[2] * sin(ypr_radians[PITCH]);
	//yh = xyz[0] * sin(ypr_radians[ROLL]) * sin(ypr_radians[PITCH]) + xyz[1] * cos(ypr_radians[ROLL]) - xyz[2] * cos(ypr_radians[PITCH]) * sin(ypr_radians[ROLL]);
	
	if (xh < 0) {
		/*
		Serial.print("Xh < 0\t(");
		Serial.print(xh);
		Serial.print(", ");
		Serial.print(yh);
		Serial.print(")\t");
		*/
		return 180 - atan(yh / xh) * 180 / M_PI;
	}
	if (xh > 0 && yh < 0) {
		/*
		Serial.print("Xh > 0, Yh < 0\t(");
		Serial.print(xh);
		Serial.print(", ");
		Serial.print(yh);
		Serial.print(")\t");
		*/
		return -atan(yh / xh) * 180 / M_PI;
	}
	if (xh > 0 && yh > 0) {
		/*
		Serial.print("Xh > 0, Yh > 0\t(");
		Serial.print(xh);
		Serial.print(", ");
		Serial.print(yh);
		Serial.print(")\t");
		*/
		return 360 - atan(yh / xh) * 180 / M_PI;
	}
}

// Calibrates for compass offsets and reading error
void calibrateCompass() {
	// check if new min or max value for all three axis
	for (int i = 0; i < 3; i++) {
		if (compass_data[i] < compass_min[i]) {	compass_min[i] = compass_data[i];}
		if (compass_data[i] > compass_max[i]) {	compass_max[i] = compass_data[i];}
	}
	/*
	float x, y, z;
	x = compass_data[0];
	y = compass_data[1];
	z = compass_data[2];
	
	float norm = sqrt(x*x + y*y + z*z);
	compass_data[0] /= norm;
	compass_data[1] /= norm;
	compass_data[2] /= norm;
	*/
	/*
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
	*/
}