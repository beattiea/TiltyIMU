
/*
float* kP, kI, kD;

void linkSettings() {
  kP = &settings.kP;
  kI = &settings.kI;
  kD = *settings.kD;
  
  /*  To set kP or settings.kP
  *kP = whatever;
      or
  settings.kP = whatever;
  
  To read kP use *kP as kP itself is just a memory address
}
*/

void setupPins() {
  //pinMode(13, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(23, INPUT);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  pinMode(BUZZER, OUTPUT);
}

void UART_ISR(void) {}
