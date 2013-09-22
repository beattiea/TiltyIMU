#include <nbwire.h>
/* This example is based on the LSM303 Tilt-Compensated Magnetometer
In setup, the accelerometer and magnetometer sections have to be
enabled, and then in the loop, each section has to be read.

The reading consists of sending the read command, and then reading
out the 6 bytes that are returned.

This non-blocking version uses the "nb" versions of endTransmission
and requestFrom, which both include a new parameter: a callback
function to be performed when the requested command is complete.

The process of reading the device is then split into 5 separate 
functions, perfomed in order. Each function sets the address of
the *following* function as the requested callback. Note that is
is basically a "split" version of Read303 from NBWireDemo1.

nbRead303: Start the process, by sending a request for a read from
the accelerometer. Set Send303Read1 as the callback.

Send303Read1: The sending of the request is done, start reading
the reply.

Send303Read2: The reply has been received, read the bytes out of
the buffer, and then send the request for a read from the 
magnetometer.

Send303Read3: The sending of the request is done, start reading
the reply.

Send303Read4: The reply has been received, read the bytes out of
the buffer, and set the Done flag.

This example uses the flags bRead303 to request a read, and 
bRead303Done to mark it completed.

*/

typedef struct vector
{
  float x, y, z;
} vector;

#define ACC_ADDRESS 		(0x30 >> 1)
#define MAG_ADDRESS 		(0x3C >> 1)

#define CTRL_REG1_A 		(0x20)
#define OUT_X_L_A  			(0x28)
#define OUT_X_H_M  			(0x03)

#define MR_REG_M  			(0x02)

extern TwoWire Wire;
bool bRead303, bRead303Done = true ;
uint8_t ubAccValues [6] ;
uint8_t ubMagValues [6] ;
long previousMillis = 0;        // will store last time LED was updated
long interval = 1000;           // interval at which to blink (milliseconds)

void En303 (void) {
    Wire.begin () ;
	//Enable Accelerometer
	Wire.beginTransmission(ACC_ADDRESS);
	Wire.send(CTRL_REG1_A);
	Wire.send(0x27); 
	Wire.endTransmission();
  
	//Enable Magnetometer
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(MR_REG_M);
	Wire.send(0x00);
	Wire.endTransmission();
  bRead303 = true ; // request a read
}

void nbRead303 () {
// either no read requested, or working on the last one
  if ((!bRead303) || (!bRead303Done)) return ;
  bRead303 = false ;  // we're doing the read,
  bRead303Done = false ; // but we're not finished.
	Wire.beginTransmission(ACC_ADDRESS);
	// assert the MSB of the address to get the accelerometer 
	// to do slave-transmit subaddress updating.
	Wire.send(OUT_X_L_A | (1 << 7)); 
	Wire.nbendTransmission(Send303Read1);
}

void Send303Read1 (int nWriteResult) {
	Wire.nbrequestFrom(ACC_ADDRESS,6, Send303Read2);
}

void Send303Read2 (int nReadResult) {
int i ;
int n303ReadBytes ;
//Serial.print ("c") ;
  n303ReadBytes = nReadResult ;
  if (n303ReadBytes > 6) n303ReadBytes = 6 ;
  for (i = 0 ; i < n303ReadBytes ; i++)
    ubAccValues [i] = Wire.receive () ;
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(OUT_X_H_M);
	Wire.nbendTransmission(Send303Read3);
}

void Send303Read3 (int nWriteResult) {
	Wire.nbrequestFrom(MAG_ADDRESS,6, Send303Read4);
}

void Send303Read4 (int nReadResult) {
int i ;
int n303ReadBytes ;
  n303ReadBytes = nReadResult ;
  if (n303ReadBytes > 6) n303ReadBytes = 6 ;
  for (i = 0 ; i < n303ReadBytes ; i++)
    ubMagValues [i] = Wire.receive () ;
  bRead303Done = true ; // finished reading.
}

void Show303Read () {
		vector a; //accelerometer	
		vector m; //magnetometer

// if still being requested, or not done
	if (bRead303 || (!bRead303Done)) return ;
	uint8_t xla = ubAccValues [0] ; // Wire.receive();
	uint8_t xha = ubAccValues [1] ; // Wire.receive();
	uint8_t yla = ubAccValues [2] ; // Wire.receive();
	uint8_t yha = ubAccValues [3] ; // Wire.receive();
	uint8_t zla = ubAccValues [4] ; // Wire.receive();
	uint8_t zha = ubAccValues [5] ; // Wire.receive();


	a.x = (xha << 8 | xla) >> 4;
	a.y = (yha << 8 | yla) >> 4;
	a.z = (zha << 8 | zla) >> 4;
	
Serial.print ("ax:") ;
Serial.println (a.x) ;
Serial.print ("ay:") ;
Serial.println (a.y) ;
Serial.print ("az:") ;
Serial.println (a.z) ;
//return ;
	//read magnetometer
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(OUT_X_H_M);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS,6);

//	while (Wire.available() < 6);

	uint8_t xhm = ubMagValues [0] ; // Wire.receive();
	uint8_t xlm = ubMagValues [1] ; // Wire.receive();
	uint8_t yhm = ubMagValues [2] ; // Wire.receive();
	uint8_t ylm = ubMagValues [3] ; // Wire.receive();
	uint8_t zhm = ubMagValues [4] ; // Wire.receive();
	uint8_t zlm = ubMagValues [5] ; // Wire.receive();

	m.x = (xhm << 8 | xlm);
	m.y = (yhm << 8 | ylm);
	m.z = (zhm << 8 | zlm);
Serial.print ("mx:") ;
Serial.println (m.x) ;
Serial.print ("my:") ;
Serial.println (m.y) ;
Serial.print ("mz:") ;
Serial.println (m.z) ;
  bRead303 = true ; // read it again
}

void setup()
{
  
  Serial.begin(57600);  // start serial for output
  En303 () ;
}

void loop()
{
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you requested a read 
    previousMillis = currentMillis;   
/* nbRead303 does *not* block, and other functions in the loop
get continued attention while the device is being read.
*/
    nbRead303 () ;
  }
  Show303Read () ;
//  delay(1000);
//  Read303 () ;
}
