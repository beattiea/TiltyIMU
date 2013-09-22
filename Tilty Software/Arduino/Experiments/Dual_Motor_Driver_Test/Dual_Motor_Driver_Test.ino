// Motor speed PWM pins
#define M1 6
#define M2 5

// Motor direction control pins
#define M1A 4
#define M1B 9
#define M2A 7
#define M2B 8


// Directions
#define FORWARD 0
#define BACKWARD 1

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(3, A0);
//   avoid using pins with LEDs attached

long oldPosition  = -999;
long newPosition = 0;

void setup() {
  Serial.begin(57600);
  Serial.println("Basic Encoder Test:");
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  delay(5000);
}

void loop() {
  setDirection(1, FORWARD);
  setDirection(2, BACKWARD);
  
  analogWrite(M2, 255);
  
  while (newPosition < 12398 * 2) {
    newPosition = myEnc.read();
    //if (newPosition != oldPosition) {
    //oldPosition = newPosition;
    //}
    Serial.println(newPosition);
    //delayMicroseconds(1);
  }
  
  Serial.println(myEnc.read());
  
  digitalWrite(M2, HIGH);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, HIGH);
  
  while (true) {}
  /*
  
  for (int i = 0; i < 255; i++) {
    analogWrite(M1, i);
    analogWrite(M2, i);
    delay(20);
  }

  for (int i = 0; i < 255; i++) {
    analogWrite(M1, 255 - i);
    analogWrite(M2, 255 - i);
    delay(20);
  }
  
  setDirection(2, FORWARD);
  setDirection(1, BACKWARD);
  
  for (int i = 0; i < 255; i++) {
    analogWrite(M1, i);
    analogWrite(M2, i);
    delay(20);
  }
  
  for (int i = 0; i < 255; i++) {
    analogWrite(M1, 255 - i);
    analogWrite(M2, 255 - i);
    delay(20);
  }
  */
  
  
}



void setDirection(int motor, bool direction) {
  if (motor == 1) {
    digitalWrite(M1A, direction);
    digitalWrite(M1B, !direction);
  }
  
  if (motor == 2) {
    digitalWrite(M2A, direction);
    digitalWrite(M2B, !direction);
  }
}
