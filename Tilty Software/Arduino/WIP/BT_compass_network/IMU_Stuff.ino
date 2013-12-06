// All of this code is used to set up and read the tilt angles from the IMU


// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;	  // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;	// expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;	 // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;		   // [w, x, y, z]		 quaternion container
VectorInt16 aa;		 // [x, y, z]			accel sensor measurements
VectorInt16 aaReal;	 // [x, y, z]			gravity-free accel sensor measurements
VectorInt16 aaWorld;	// [x, y, z]			world-frame accel sensor measurements
VectorFloat gravity;	// [x, y, z]			gravity vector
float euler[3];		 // [psi, theta, phi]	Euler angle container

volatile bool mpuInterrupt = false;	 // indicates whether MPU interrupt pin has gone high

#define OUTPUT_READABLE_YAWPITCHROLL

void setupIMU() {
    //Serial.println("\tInitializing DMP...");
    devStatus = imu.dmpInitialize();

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		//Serial.println(F("\tEnabling DMP..."));
		imu.setDMPEnabled(true);

		mpuIntStatus = imu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println("\tDMP ready! Waiting for first interrupt...");
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = imu.dmpGetFIFOPacketSize();
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print("\tDMP Initialization failed (code ");
		Serial.print(devStatus);
		Serial.println(")");
	}
}

void readIMU() {
	// if programming failed, don't try to do anything
		if (!dmpReady) return;

		// reset interrupt flag and get INT_STATUS byte
		mpuInterrupt = false;
		mpuIntStatus = imu.getIntStatus() & 0x12;

		while (!mpuIntStatus) {
			mpuIntStatus = imu.getIntStatus() & 0x12;
			//Serial.println(mpuIntStatus);
		}

		// get current FIFO count
		fifoCount = imu.getFIFOCount();

		// check for overflow (this should never happen unless our code is too inefficient)
		if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
			// reset so we can continue cleanly
			imu.resetFIFO();
			Serial.println("FIFO overflow!");

		// otherwise, check for DMP data ready interrupt (this should happen frequently)
		} else if (mpuIntStatus & 0x02) {
			// wait for correct available data length, should be a VERY short wait
			while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

			// read a packet from FIFO
			imu.getFIFOBytes(fifoBuffer, packetSize);

			// track FIFO count here in case there is > 1 packet available
			// (this lets us immediately read more without waiting for an interrupt)
			fifoCount -= packetSize;

			// display Euler angles in degrees
			imu.dmpGetQuaternion(&q, fifoBuffer);
			imu.dmpGetGravity(&gravity, &q);
			imu.dmpGetYawPitchRoll(ypr, &q, &gravity);
			ypr[0] *= 180/M_PI;
			ypr[1] *= 180/M_PI;
			ypr[2] *= 180/M_PI;
			
			//if (ypr[PITCH] < 0) {	ypr[PITCH] += 360;}
			//if (ypr[ROLL] < 0) {	ypr[ROLL] += 360;}
			//Serial.println(ypr[PITCH]);
			//Serial.println(ypr[ROLL]);
	}
}
