#define OUTPUT_READABLE_EULER
#define LED_PIN 13

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

void setupDMP() {
    //Serial.println("\tInitializing DMP...");
    devStatus = mpu.dmpInitialize();

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		//Serial.println(F("\tEnabling DMP..."));
		mpu.setDMPEnabled(true);

		mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println("\tDMP ready! Waiting for first interrupt...");
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		//devStatus == 1 ? SOS(devStatus, "\tInitial DMP memory load failed") : SOS(devStatus, "\tDMP configuration updates failed");
	}
}

bool blinkState = false;

volatile bool mpuInterrupt = false;	 // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
	mpuInterrupt = true;
}

// ================================================================
// ===					MAIN PROGRAM LOOP					 ===
// ================================================================

void readDMP() {
	// if programming failed, don't try to do anything
	if (!dmpReady) return;

	// reset interrupt flag and get INT_STATUS byte
	mpuInterrupt = false;
	mpuIntStatus = mpu.getIntStatus() & 0x12;
	
	while (!mpuIntStatus) {
		mpuIntStatus = mpu.getIntStatus() & 0x12;
		//Serial.println(mpuIntStatus);
	}

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		Serial.println(F("FIFO overflow!"));

	// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (mpuIntStatus & 0x02) {
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);
		
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;

		#ifdef OUTPUT_READABLE_EULER
			// display Euler angles in degrees
			mpu.dmpGetQuaternion(&q, fifoBuffer);
			mpu.dmpGetEuler(ypr, &q);
			ypr[0] *= 180/M_PI;
			ypr[1] *= 180/M_PI;
			ypr[2] *= 180/M_PI;
		#endif

		#ifdef OUTPUT_READABLE_YAWPITCHROLL
			// display Euler angles in degrees
			//mpu.dmpGetQuaternion(&q, fifoBuffer);
			mpu.dmpGetGravity(&gravity, &q);
			mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
			Serial.print("ypr\t");
			Serial.print(ypr[0] * 180/M_PI);
			Serial.print("\t");
			Serial.print(ypr[1] * 180/M_PI);
			Serial.print("\t");
			Serial.println(ypr[2] * 180/M_PI);
		#endif

		// blink LED to indicate activity
		blinkState = !blinkState;
		digitalWrite(LED_PIN, blinkState);
		//Serial.println();
	}
}