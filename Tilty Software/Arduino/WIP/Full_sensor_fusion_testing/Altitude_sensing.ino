float bias = 0.98;

float sensor_alt;

long alt_now;
long alt_dt_us;
float alt_dt;

void computeAltitude() {
	if (alt.getDataReady()) {
		sensor_alt = alt.readAltitudeM();
		alt.forceMeasurement();
		alt_now = micros();
		alt_dt = (alt_now - alt_dt_us) / 1000000.0;
		altitude = bias * altitude + (axyz[2] * alt_dt) + (1 - bias) * sensor_alt;
		alt_dt_us = alt_now;
	}
	/*
	while (true) {
		Serial.println(alt.readAltitudeM());
		alt.forceMeasurement();
		delay(5);
	}
	*/
	
	//Serial.print("Altitude fusion: ");
	Serial.print(altitude);
	//Serial.print("\t\tSensor reading: ");
	Serial.print(", ");
	Serial.println(sensor_alt);
}