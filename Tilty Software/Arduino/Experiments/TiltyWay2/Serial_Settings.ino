/*
Change code to read from serial and bluetooth then report values to the necessary functions
Can use serialEvent() and serialEvent2() to read data when it's available
*/

int float_precision = 5;

void checkSerial() {
  if (myPort.available()) {
    char data = myPort.read();
    switch (data) {
      case (SET_COMMAND): {  setVariable(); break;}
      case (READ_COMMAND): {  readVariable(); break;}
      case (STREAMING_COMMAND): {  setStreaming(); break;}
      case (PING): {  myPort.println(CONFIRM); connected = true; break;}
      case (FORWARD): {  remoteControl(data); break;}
      case (STEERING): {  remoteControl(data); break;}
      }
  }
  
  if (STREAM_P) {  myPort.print(VARIABLE_P);  myPort.println(P, 5);}
  if (STREAM_I) {  myPort.print(VARIABLE_I);  myPort.println(I, 5);}
  if (STREAM_D) {  myPort.print(VARIABLE_D);  myPort.println(D, 5);}
  if (STREAM_ANGLE) {  myPort.print(VARIABLE_ANGLE);  myPort.println(pitch, 5);}
}

/*  This code will eventually sense whether the TeensyWay is connected to a computer  */
void ping() {
  
}



void readPitch() {
  
}

void readRoll() {
  
}



/*  Runs the function to set the specified variable  */
void setVariable() {
  while (!myPort.available()) {}
  switch (myPort.read()) {
    case (VARIABLE_kP): {  setkP(); break;}
    case (VARIABLE_kI): {  setkI(); break;}
    case (VARIABLE_kD): {  setkD(); break;}
    case (VARIABLE_kS): {  setkS(); break;}
    case (VARIABLE_OFFSET): {  setOffset(); break;}
    case (VARIABLE_SOFFSET): {  setSteeringOffset(); break;}
  }
}

/*  Reports the value of the specified variable  */
void readVariable() {
  while (!myPort.available()) {}
  switch (myPort.read()) {
    case (VARIABLE_kP): {  myPort.print(VARIABLE_kP);  myPort.println(kP, float_precision); break;}
    case (VARIABLE_kI): {  myPort.print(VARIABLE_kI);  myPort.println(kI, float_precision); break;}
    case (VARIABLE_kD): {  myPort.print(VARIABLE_kD);  myPort.println(kD, float_precision); break;}
    case (VARIABLE_P): {  myPort.print(VARIABLE_P); myPort.println(P, float_precision); break;} 
    case (VARIABLE_I): {  myPort.print(VARIABLE_I); myPort.println(I, float_precision); break;}
    case (VARIABLE_D): {  myPort.print(VARIABLE_D); myPort.println(D, float_precision); break;}
    case (VARIABLE_kS): {  myPort.print(VARIABLE_kS); myPort.println(kS, float_precision); break;}
    case (VARIABLE_S): {  myPort.print(VARIABLE_S); myPort.println(S, float_precision); break;}
    case (VARIABLE_ANGLE): {  myPort.print(VARIABLE_ANGLE); myPort.println(pitch, float_precision); break;}
    case (VARIABLE_OFFSET): {  myPort.print(VARIABLE_OFFSET); myPort.println(pitch_offset, float_precision); break;}
    case (VARIABLE_SPEED): {  myPort.print(VARIABLE_SPEED); myPort.println(speed_limit, float_precision); break;}
    case (VARIABLE_KICK): {  myPort.print(VARIABLE_KICK); myPort.println(kickback, float_precision); break;}
    //case (VARIABLE_TRIM): {  printTrimPots(); break;}
  }
}

/*  Sets streaming data either on or off  */
void setStreaming() {
  char serial_input;
  while (!myPort.available()) {}
  serial_input = myPort.read();
  while (!myPort.available()) {}
  switch (serial_input) {
    case (VARIABLE_P): {  STREAM_P = myPort.read() - 0x30; break;}
    case (VARIABLE_I): {  STREAM_I = myPort.read() - 0x30; break;}
    case (VARIABLE_D): {  STREAM_D = myPort.read() - 0x30; break;}
    case (VARIABLE_ANGLE): {  STREAM_ANGLE = myPort.read() - 0x30; break;}
    case (VARIABLE_S): {  STREAM_S = myPort.read() - 0x30; break;}
    case (VARIABLE_LOOP): {  STREAM_LOOP = myPort.read() - 0x30; break;}
  }
}



void setkP() {
  while (!myPort.available()) {}
  kP = myPort.parseFloat();
}

void setkI() {
  while (!myPort.available()) {}
  kI = myPort.parseFloat();
  if (kI == 0) {  I = 0;}
}

void setkD() {
  while (!myPort.available()) {}
  kD = myPort.parseFloat();
}

void setOffset() {
  while (!myPort.available()) {}
  pitch_offset = myPort.parseFloat();
}

void setkS() {
  while (!myPort.available()) {}
  kS = myPort.parseFloat();
}

void setSteeringOffset() {
  while (!myPort.available()) {}
}


