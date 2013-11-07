float tiltCompensateCompass(float *xyz) {
	for (int i = 0; i < 3; i++) {
		ypr_radians[i] = ypr[i] * M_PI / 180;
	}
	
	float xh = xyz[0] * cos(ypr_radians[PITCH]) + xyz[2] * sin(ypr_radians[PITCH]);
	float yh = xyz[0] * sin(ypr_radians[ROLL]) * sin(ypr_radians[PITCH]) + xyz[1] * cos(ypr_radians[ROLL]) - xyz[2] * sin(ypr_radians[ROLL]) * cos(ypr_radians[PITCH]);
	
	return atan(yh / xh) * 180/M_PI;
}