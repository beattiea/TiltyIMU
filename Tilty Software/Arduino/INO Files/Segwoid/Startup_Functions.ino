void loadSavedSettings() {
  if (EEPROM.read(0) != 1) {  setupSettings();}
  else {  load(0, settings);}
  linkSettings();//  Used to link settings class variables to global variables used for calculations and held in RAM
}

void setupSettings() {
  settings.address = 0;
  settings.kP = 10.0;//  Very stiff at 15.0
  settings.kI = 110.0;//Very stiff at 70.0...  27.5 on baby one, works on big one
  settings.kD = 0.20;//0.125;//(settings.kP / 6.5) * 0.125;//  0.15 on baby one
  settings.kS = 0.065;//  0.075 on baby one
  settings.angleOffset = 0.0;//  2.13 works well (measured at startup and steady state
  settings.speedLimit = 375;
  settings.kickback = 10;//  Needs to be changed to float in library
  settings.steeringMin = 383 + 70;
  settings.steeringMax = 383 - 70;
  settings.steeringOffset = 0;
  settings.name = "Default";
  //save(0, settings);
}

void linkSettings() {
  kP = settings.kP;
  kI = settings.kI;
  kD = settings.kD;
  kS = settings.kS;
  pitch_offset = settings.angleOffset;
  speed_limit = settings.speedLimit;
}

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
