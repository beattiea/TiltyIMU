#include <nbwire.h>
/* See NBWireDemo2 for documentation
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
}

void Read303 () {
		vector a; //accelerometer	
		vector m; //magnetometer

	//read accelerometer
	Wire.beginTransmission(ACC_ADDRESS);
	// assert the MSB of the address to get the accelerometer 
	// to do slave-transmit subaddress updating.
	Wire.send(OUT_X_L_A | (1 << 7)); 
	Wire.endTransmission();
	Wire.requestFrom(ACC_ADDRESS,6);

	while (Wire.available() < 6);
	
	uint8_t xla = Wire.receive();
	uint8_t xha = Wire.receive();
	uint8_t yla = Wire.receive();
	uint8_t yha = Wire.receive();
	uint8_t zla = Wire.receive();
	uint8_t zha = Wire.receive();


	a.x = (xha << 8 | xla) >> 4;
	a.y = (yha << 8 | yla) >> 4;
	a.z = (zha << 8 | zla) >> 4;
	
Serial.print ("ax:") ;
Serial.println (a.x) ;
Serial.print ("ay:") ;
Serial.println (a.y) ;
Serial.print ("az:") ;
Serial.println (a.z) ;
	//read magnetometer
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(OUT_X_H_M);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS,6);

	while (Wire.available() < 6);

	uint8_t xhm = Wire.receive();
	uint8_t xlm = Wire.receive();
	uint8_t yhm = Wire.receive();
	uint8_t ylm = Wire.receive();
	uint8_t zhm = Wire.receive();
	uint8_t zlm = Wire.receive();

	m.x = (xhm << 8 | xlm);
	m.y = (yhm << 8 | ylm);
	m.z = (zhm << 8 | zlm);
Serial.print ("mx:") ;
Serial.println (m.x) ;
Serial.print ("my:") ;
Serial.println (m.y) ;
Serial.print ("mz:") ;
Serial.println (m.z) ;
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
/* Read303 blocks until the communication with the device is
complete. Any other functions performed in this loop 
come to a halt until it's finished.
*/
    Read303 () ;
  }
}
