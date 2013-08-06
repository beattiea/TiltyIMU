void setup() {
  Serial.begin(38400);
  PORTD = 0b00000000;
}

byte state = 0b00000000;
int time[4];
int start[4];
boolean printNow = true;

void loop() {
  /*
  if (digitalRead(3) && !bitRead(state, 0)) {
    bitSet(state, 0);
    start[0] = micros();
  }
  if (!digitalRead(3) && bitRead(state, 0))  {
    bitClear(state, 0);
    time[0] = micros() - start[0];
  }
  
  if (digitalRead(2) && !bitRead(state, 1)) {
    bitSet(state, 1);
    start[1] = start[0];
  }
  if (!digitalRead(2) && bitRead(state, 1))  {
    bitClear(state, 1);
    time[1] = micros() - start[1];
  }
  
  
  if (digitalRead(0) && !bitRead(state, 2)) {
    bitSet(state, 2);
    start[2] = start[1];
  }
  if (!digitalRead(0) && bitRead(state, 2))  {
    bitClear(state, 2);
    time[2] = micros() - start[2];
  }
  
  
  if (digitalRead(1) && !bitRead(state, 4)) {
    bitSet(state, 4);
    start[3] = start[2];
  }
  if (!digitalRead(1) && bitRead(state, 4))  {
    bitClear(state, 4);
    time[3] = micros() - start[3];
    printNow = true;
  }
  */
  time[0] = pulseIn(3, HIGH, 21000);
  time[1] = pulseIn(2, HIGH, 21000);
  time[2] = pulseIn(0, HIGH, 21000);
  time[3] = pulseIn(1, HIGH, 21000);
  
  if (printNow) {
    Serial.print(time[0]);// - 3);
    Serial.print(",");
    Serial.print(time[1]);// - time[0] - 3);
    Serial.print(",");
    Serial.print(time[2]);// - time[1] - 3);
    Serial.print(",");
    Serial.print(time[3]);// - time[2] - 3);
    Serial.println();
    //printNow = false;
  }
}
