#include <Wire.h>
#include <HMC58X3.h>

HMC5883 magn;

void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  
  magn.init(true); // Dont set mode yet, we'll do that later on.
}

void loop() { 
  int ix,iy,iz;
  delay(10);
  
  // Get values, as ints and floats.
  magn.getRaw(&ix,&iy,&iz);
  
  Serial.print(ix);
  Serial.print(",");
  Serial.print(iy);
  Serial.print(",");
  Serial.print(iz);
  Serial.println(",");
}
