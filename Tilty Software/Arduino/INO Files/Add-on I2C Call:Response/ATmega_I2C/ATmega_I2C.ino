#include <Wire.h>

volatile int x = 0;

void setup() {
  //TWBR = 200000L;
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  
  Wire.begin(0x15);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(1);
  analogWrite(6, map(x, 0, 9, 0, 255));
}


void requestEvent() {
  Wire.write(x);
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    x = Wire.read();
  }
}
