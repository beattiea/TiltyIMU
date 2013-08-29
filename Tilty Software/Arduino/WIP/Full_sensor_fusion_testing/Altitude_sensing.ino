#define OUTPUT_ALTITUDE

float bias = 0.5;

long alt_now;
long alt_dt_us;
float alt_dt;
float alt_old;
float vertical_vel = 0;

void computeAltitude() {
	if (alt.getDataReady()) {
		sensor_alt = alt.readAltitudeM();
		alt.forceMeasurement();
		alt_now = micros();
		alt_dt = (alt_now - alt_dt_us) / 1000000.0;
		
		vertical_vel += axyz[2] * alt_dt;
		
		altitude = bias * (altitude + vertical_vel) + (1 - bias) * sensor_alt;
		alt_dt_us = alt_now;
	}
	
	else {
		alt_now = micros();
		alt_dt = (alt_now - alt_dt_us) / 1000000.0;
		
		vertical_vel += axyz[2] * alt_dt;
		
		altitude += vertical_vel * alt_dt;
		alt_dt_us = alt_now;
	}
	
	#ifdef OUTPUT_ALTITUDE
		//Serial.print("Altitude fusion: ");
		Serial.print(altitude);
		//Serial.print("m\t\tSensor reading: ");
		Serial.print(", ");
		Serial.print(sensor_alt);
		Serial.print(", ");
		Serial.print(vertical_vel);
                //Serial.print("\t\tZ Acceleration: ");
                //Serial.print(axyz[2]);
                Serial.println();
	#endif
}
