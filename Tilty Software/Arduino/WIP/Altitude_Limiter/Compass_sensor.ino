//#define OUTPUT_HEADING

float yaw_bias = 0.5;

long magn_now;
long magn_dt_us;
float magn_dt;

float pitch_rad;
float roll_rad;

int16_t ix_min = -1836, ix_max = 738;
int16_t iy_min = -1399, iy_max = 1227;
int16_t iz_min = -1031, iz_max = 1404;

int16_t ix_offset, iy_offset, iz_offset;

void readCompass() { 
	
	magn.getValues(&ix,&iy,&iz);
	
	if (ix < ix_min) {	ix_min = ix;}
	if (ix > ix_max) {	ix_max = ix;}
	if (iy < iy_min) {	iy_min = iy;}
	if (iy > iy_max) {	iy_max = iy;}
	if (iz < iz_min) {	iz_min = iz;}
	if (iz > iz_max) {	iz_max = iz;}
	
	ix_offset = (ix_min + ix_max) / 2;
	iy_offset = (iy_min + iy_max) / 2;
	iz_offset = (iz_min + iz_max) / 2;
	
	ix -= ix_offset;
	iy -= iy_offset;
	iz -= iz_offset;
	
	pitch_rad = ypr[PITCH_INDEX] * (M_PI / 180);
	roll_rad = ypr[ROLL_INDEX] * (M_PI / 180);
	
	int xH = ix * cos(pitch_rad) + iz * sin(pitch_rad);
	int yH = ix * sin(roll_rad) * sin(pitch_rad) + iy * cos(roll_rad) - iz * sin(roll_rad) * cos(pitch_rad);
	
	heading = atan2(yH, xH);
	heading += M_PI;
	if(heading < 0) {
		//heading += 2 * M_PI;
	}
	heading *= 180/M_PI;
	
	#ifdef OUTPUT_HEADING
		Serial.print(" Heading: ");
		Serial.println(heading); 
	#endif
}

float old_yaw = 0;

void calculateYaw() {
	float d_yaw;
	
	if (magn.getDataReady()) {
		readCompass();
		
		magn_now = micros();
		magn_dt = (magn_now - magn_dt_us) / 1000000.0;
		
		yaw = yaw_bias * yaw +  (ypr[YAW_INDEX] - old_yaw) * magn_dt + (1 - yaw_bias) * heading; // SHOULD USE GYRO RATE INSTEAD OF dYAW
		magn_dt_us = magn_now;
		d_yaw = ypr[YAW_INDEX] - old_yaw;
		old_yaw = ypr[YAW_INDEX];
	}
	
	else {
		magn_now = micros();
		magn_dt = (magn_now - magn_dt_us) / 1000000.0;
		yaw += (ypr[YAW_INDEX] - old_yaw) * magn_dt;
		magn_dt_us = magn_now;		
	}
}
