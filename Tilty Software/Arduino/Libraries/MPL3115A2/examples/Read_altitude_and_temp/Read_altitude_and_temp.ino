#include <MPL3115A2.h>
#include <Wire.h>

MPL3115A2 altimeter;

void setup() {
  Wire.begin();
  altimeter.init();
  Serial.begin(115200);
}

void loop() {
  Serial.print("Altitude: ");
  Serial.print(altimeter.readAltitudeM());//  Use readAltitudeF() for feet
  Serial.println(" meters");
  
  Serial.print("Temperature: ");
  Serial.print(altimeter.readTempC());//  Use readTempF() for fahrenheit
  Serial.println(" degrees C");
  
  while (!altimeter.checkData()) {  delay(25);}
}
