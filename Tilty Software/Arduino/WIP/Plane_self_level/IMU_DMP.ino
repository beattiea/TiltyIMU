#define OUTPUT_READABLE_YAWPITCHROLL

#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t imuIntStatus;   // holds actual interrupt status byte from MPU
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


// ================================================================
// ===			   INTERRUPT DETECTION ROUTINE				===
// ================================================================

volatile bool imuInterrupt = false;	 // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
	imuInterrupt = true;
}



// ================================================================
// ===					  INITIAL SETUP					   ===
// ================================================================

void setupDMP() {
	// join I2C bus (I2Cdev library doesn't do this automatically)

	// initialize myPort communication
	// (115200 chosen because it is required for Teapot Demo output, but it's
	// really up to you depending on your project)

	// NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
	// Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
	// the baud timing being too misaligned with processor ticks. You must use
	// 38400 or slower in these cases, or use some kind of external separate
	// crystal solution for the UART timer.

	// initialize device
	myPort.println(F("Initializing I2C devices..."));
	imu.initialize();

	// verify connection
	myPort.println(F("Testing device connections..."));
	myPort.println(imu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

	// load and configure the DMP
	myPort.println(F("Initializing DMP..."));
	devStatus = imu.dmpInitialize();
	
	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		myPort.println(F("Enabling DMP..."));
		imu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		myPort.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		attachInterrupt(6, dmpDataReady, RISING);
		imuIntStatus = imu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		myPort.println(F("DMP ready! Waiting for first interrupt..."));
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = imu.dmpGetFIFOPacketSize();
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		myPort.print(F("DMP Initialization failed (code "));
		myPort.print(devStatus);
		myPort.println(F(")"));
	}
	
	while (abs(ypr[1]) > 3 || abs(ypr[2]) > 3 ) {
		readDMP();
	}

	// configure LED for output
	pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===				    MAIN SENSOR READ LOOP				     ===
// ================================================================

void readDMP() {
	// reset interrupt flag and get INT_STATUS byte
	imuInterrupt = false;
	imuIntStatus = imu.getIntStatus() & 0x12;
	
	while (!imuIntStatus) {
		imuIntStatus = imu.getIntStatus() & 0x12;
	}

	// get current FIFO count
	fifoCount = imu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((imuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		imu.resetFIFO();
		myPort.println(F("FIFO overflow!"));

	// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (imuIntStatus & 0x02) {
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

		// read a packet from FIFO
		imu.getFIFOBytes(fifoBuffer, packetSize);
		
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;


		#ifdef OUTPUT_READABLE_YAWPITCHROLL
			// display Euler angles in degrees
			imu.dmpGetQuaternion(&q, fifoBuffer);
			imu.dmpGetGravity(&gravity, &q);
			imu.dmpGetYawPitchRoll(ypr, &q, &gravity);
			ypr[0] *= 180/M_PI;
			ypr[1] *= 180/M_PI;
			ypr[2] *= 180/M_PI;
			
			ypr[PITCH_INDEX] -= pitch_offset;
			ypr[ROLL_INDEX] -= roll_offset;
			
			myPort.print("ypr\t");
			myPort.print(ypr[YAW_INDEX]);
			myPort.print("\t");
			myPort.print(ypr[PITCH_INDEX]);
			myPort.print("\t");
			myPort.print(ypr[ROLL_INDEX]);
			myPort.print("\t");
			myPort.println(pitch_offset);
		#endif

		// blink LED to indicate activity
		blinkState = !blinkState;
		digitalWrite(LED_PIN, blinkState);
	}
}