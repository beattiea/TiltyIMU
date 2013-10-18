/*
void loadSavedValues() {
  if (checkEEPROMsaved(YAW_OFFSET_ADDRESS)) {  yaw_offset = loadFloat(YAW_OFFSET_ADDRESS);}
  if (checkEEPROMsaved(PITCH_OFFSET_ADDRESS)) {  pitch_offset = loadFloat(PITCH_OFFSET_ADDRESS);}
  if (checkEEPROMsaved(ROLL_OFFSET_ADDRESS)) {  roll_offset = loadFloat(ROLL_OFFSET_ADDRESS);}
  

  if (checkEEPROMsaved(kP_ADDRESS)) {  kP = loadFloat(kP_ADDRESS);}
  if (checkEEPROMsaved(kI_ADDRESS)) {  kI = loadFloat(kI_ADDRESS);}
  if (checkEEPROMsaved(kD_ADDRESS)) {  kD = loadFloat(kD_ADDRESS);}
  

  if (checkEEPROMsaved(STEERING_MIN_ADDRESS)) {  steering_min_val = loadInt(STEERING_MIN_ADDRESS);}
  if (checkEEPROMsaved(STEERING_MAX_ADDRESS)) {  steering_max_val = loadInt(STEERING_MAX_ADDRESS);}
}
*/

void loadSavedSettings() {
  if (EEPROM.read(0) != 1) {  setupSettings();}
  else {  load(0, settings);}
  linkSettings();//  Used to link settings class variables to global variables used for calculations and held in RAM
}

void setupSettings() {
  settings.address = 0;
  settings.kP = 6.5;//  6.5 on baby one
  settings.kI = 27.5;//  27.5 on baby one
  settings.kD = 0.125;//  0.15 on baby one
  settings.kS = 0.0;//  0.075 on baby one
  settings.angleOffset = -1.75;
  settings.kickback = 10;
  settings.steeringMin = 131;
  settings.steeringMax = 305;
  settings.steeringOffset = 0;
  settings.name = "Default";
  save(0, settings);
}

void linkSettings() {
  kP = settings.kP;
  kI = settings.kI;
  kD = settings.kD;
  kS = settings.kS;
  pitch_offset = settings.angleOffset;
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
