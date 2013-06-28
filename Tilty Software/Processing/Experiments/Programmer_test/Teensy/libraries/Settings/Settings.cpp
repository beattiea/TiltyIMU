#include "Settings.h"

/*	Save functions	*/
void Settings::savekP(float value) {
	save(address + KP_ADDRESS, value);
}
void Settings::savekP() {
	save(address + KP_ADDRESS, kP);
}

void Settings::savekI(float value) {
	save(address + KI_ADDRESS, value);
}
void Settings::savekI() {
	save(address + KI_ADDRESS, kI);
}

void Settings::savekD(float value) {
	save(address + KD_ADDRESS, value);
}
void Settings::savekD() {
	save(address + KD_ADDRESS, kD);
}

void Settings::savekS(int value) {
	save(address + KS_ADDRESS, value);
}
void Settings::savekS() {
	save(address + KS_ADDRESS, kS);
}

void Settings::saveAngleOffset(float value) {
	save(address + ANGLE_OFFSET_ADDRESS, value);
}
void Settings::saveAngleOffset() {
	save(address + ANGLE_OFFSET_ADDRESS, angleOffset);
}

void Settings::saveLoopTime(int value) {
	save(address + LOOP_TIME_ADDRESS, value);
}
void Settings::saveLoopTime() {
	save(address + LOOP_TIME_ADDRESS, loopTime);
}

void Settings::saveSpeedLimit(int value) {
	save(address + SPEED_LIMIT_ADDRESS, value);
}
void Settings::saveSpeedLimit() {
	save(address + SPEED_LIMIT_ADDRESS, speedLimit);
}

void Settings::saveKickback(int value) {
	save(address + KICKBACK_ADDRESS, value);
}
void Settings::saveKickback() {
	save(address + KICKBACK_ADDRESS, kickback);
}

void Settings::savekB(float value) {
	save(address + kB_ADDRESS, value);
}
void Settings::savekB() {
	save(address + kB_ADDRESS, kB);
}

void Settings::saveSteeringMin(int value) {
	save(address + STEER_MIN_ADDRESS, value);
}
void Settings::saveSteeringMin() {
	save(address + STEER_MIN_ADDRESS, steeringMin);
}

void Settings::saveSteeringMax(int value) {
	save(address + STEER_MAX_ADDRESS, value);
}
void Settings::saveSteeringMax() {
	save(address + STEER_MAX_ADDRESS, steeringMax);
}

void Settings::saveSteeringOffset(int value) {
	save(address + STEER_OFFSET_ADDRESS, value);
}
void Settings::saveSteeringOffset() {
	save(address + STEER_OFFSET_ADDRESS, steeringMax);
}

void Settings::saveName(String value) {
	save(address + NAME_ADDRESS, value);
}
void Settings::saveName() {
	save(address + NAME_ADDRESS, name);
}



/*	Load Functions	*/
float Settings::loadkP() {
	load(address + KP_ADDRESS, kP);
	return kP;
}

float Settings::loadkI() {
	load(address + KI_ADDRESS, kI);
	return kI;
}

float Settings::loadkD() {
	load(address + KD_ADDRESS, kD);
	return kD;
}

float Settings::loadkS() {
	load(address + KS_ADDRESS, kS);
	return kS;
}

float Settings::loadAngleOffset() {
	load(address + ANGLE_OFFSET_ADDRESS, angleOffset);
	return angleOffset;
}

int Settings::loadLoopTime() {
	load(address + LOOP_TIME_ADDRESS, loopTime);
	return loopTime;
}

int Settings::loadSpeedLimit() {
	load(address + SPEED_LIMIT_ADDRESS, speedLimit);
	return speedLimit;
}

int Settings::loadKickback() {
	load(address + KICKBACK_ADDRESS, kickback);
	return kickback;
}

float Settings::loadkB() {
	load(address + kB_ADDRESS, kB);
	return kB;
}

int Settings::loadSteeringMin() {
	load(address + STEER_MIN_ADDRESS, steeringMin);
	return steeringMin;
}

int Settings::loadSteeringMax() {
	load(address + STEER_MAX_ADDRESS, steeringMax);
	return steeringMax;
}

int Settings::loadSteeringOffset() {
	load(address + STEER_OFFSET_ADDRESS, steeringOffset);
	return steeringOffset;
}

void Settings::loadName() {
	load(address + NAME_ADDRESS, name);
}