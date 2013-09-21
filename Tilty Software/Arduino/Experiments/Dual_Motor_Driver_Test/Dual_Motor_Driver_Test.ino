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

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
}

void loop() {
  setDirection(1, FORWARD);
  setDirection(2, BACKWARD);
  
  for (int i = 0; i < 255; i++) {
    analogWrite(M1, i);
    analogWrite(M2, i);
    delay(20);
  }
  
  
  
  
  while (true) {
    analogWrite(M1, 255);
    analogWrite(M2, 255);
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
}// Motor speed PWM pins
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

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
}

void loop() {
  setDirection(1, FORWARD);
  setDirection(2, BACKWARD);
  
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
