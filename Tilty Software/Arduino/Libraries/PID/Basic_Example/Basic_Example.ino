#include <PID.h>

float input;
float PID_output;

PID pid = PID(&input, &PID_output, 3, 0.5, 0.1, FORWARD);

void setup() {
	Serial.begin(115200);
	while (!Serial) {}
	
	pid.setPLimits(-150, 150);
	pid.setILimits(-125, 125);
	pid.setDLimits(-5, 5);
	pid.setLimits(-200, 200);
}

void loop() {
	input = random(-100, 100);
	pid.update();
	Serial.print("PID: ");
	Serial.println(PID_output);
	
	if (pid.limited()) {
		Serial.println("PID overflow!");
		pid.reset();
		delay(1000);
	}
	delay(10);
}

/*
==========================Constructors=================================
	PID();
	PID(float kP, float kI, float kD);
	PID(float kP, float kI, float kD, bool direction);
	PID(float &inputVariable, float &outputVariable);
	PID(float &inputVariable, float &outputVariable, float kP, float kI, float kD);
	PID(float &inputVariable, float &outputVariable, float kP, float kI, float kD, bool _dir);
	
=========================Update Functions==============================
	float update();
	float update(int inputVariable);
	float update(float inputVariable);
	
======================Control Setting Functions===========================
	void setScalars(float kP, float kI, float kD);
	void setLimits(float lowerLimit, float upperLimit);
	void setPLimits(float lowerLimit, float upperLimit);
	void setILimits(float lowerLimit, float upperLimit);
	void setDLimits(float lowerLimit, float upperLimit);
	void setDirection(bool direction); // FORWARD or REVERSE
	void setInputTriggers(float lowerLimit, float upperLimit); // Sets limits for what inputs will trigger the PID
	void setInputConstraints(float lowerLimit, float upperLimit); // Sets limits for what inputs will turn off the PID
	
=======================Error Handling Functions==========================
	void reset();
	boolean limited(); // checks if total PID output has met or exceeded set limits
	
========================Get Setting Functions============================
	int8_t getDirection(); // -1 for Reverse, 1 for Forward
	float getkP();
	float getkI();
	float getkD();
===========================Public Variables==============================
	// PID scalars
	float kP = 0;
	float kI = 0;
	float kD = 0;
	
	// Individual components of overall PID value
	float Pvalue = 0;
	float Ivalue = 0;
	float Dvalue = 0;
	
	// All limits default to maximum variable size
	float upperLimit = 2147483647;
	float lowerLimit = -2147483647;
	float upperPLimit = 2147483647;
	float lowerPLimit = -2147483647;
	float upperILimit = 2147483647;
	float lowerILimit = -2147483647;
	float upperDLimit = 2147483647;
	float lowerDLimit = -2147483647;
*/