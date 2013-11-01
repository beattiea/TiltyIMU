void setupBangs(int x, int y, int x_spacing) {
  setupReadkPBang(x, y);
  setupReadkIBang(x, y * 2);
  setupReadkDBang(x, y * 3);
  
  setupSetkPBang(x + x_spacing, y);
  setupSetkIBang(x + x_spacing, y * 2);
  setupSetkDBang(x + x_spacing, y * 3);
  
  setupSavekPBang(x + x_spacing * 2, y);
  setupSavekIBang(x + x_spacing * 2, y * 2);
  setupSavekDBang(x + x_spacing * 2, y * 3);
  
  setupLoadkPBang(x + x_spacing * 3, y);
  setupLoadkIBang(x + x_spacing * 3, y * 2);
  setupLoadkDBang(x + x_spacing * 3, y * 3);
  
  setupAutoConnectBang(175, 4);
  
  setupClearBang(475, 4);
}

void setupReadkPBang(int x, int y) {
  cp5.addBang("readkP")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Read kP")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupReadkIBang(int x, int y) {
  cp5.addBang("readkI")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Read kI")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupReadkDBang(int x, int y) {
  cp5.addBang("readkD")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Read kD")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}




void setupSetkPBang(int x, int y) {
  cp5.addBang("setkP")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Set kP")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupSetkIBang(int x, int y) {
  cp5.addBang("setkI")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Set kI")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupSetkDBang(int x, int y) {
  cp5.addBang("setkD")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Set kD")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}




void setupSavekPBang(int x, int y) {
  cp5.addBang("savekP")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Save kP")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupSavekIBang(int x, int y) {
  cp5.addBang("savekI")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Save kI")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupSavekDBang(int x, int y) {
  cp5.addBang("savekD")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Save kD")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}



void setupLoadkPBang(int x, int y) {
  cp5.addBang("loadkP")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Load kP")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupLoadkIBang(int x, int y) {
  cp5.addBang("loadkI")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Load kI")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupLoadkDBang(int x, int y) {
  cp5.addBang("loadkD")
     .setPosition(x, y)
     .setSize(40, 25)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Load kD")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}



void setupAutoConnectBang(int x, int y) {
  cp5.addBang("refresh")
     .setPosition(x, y)
     .setSize(50, 20)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Refresh")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, CENTER)
     ;
}

void setupClearBang(int x, int y) {
  cp5.addBang("clearSerial")
     .setPosition(x, y)
     .setSize(75, 20)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("Clear Serial")
     .getCaptionLabel().setFont(createFont("arial", 9))
     .align(CENTER, BOTTOM)
     ;
}

void clearSerial() {
  myPort.clear();
}

//  NEED NEW BANG BUTTON ROUTINES TO INTERFACE WITH NEW SERIAL AS BELOW
void readkP() {  readVar(VARIABLE_kP);}
void setkP() {  kP = float(kPval.getText()); setVarFloat(VARIABLE_kP, kP);}
void savekP() {  kP = float(kPval.getText()); saveVarFloat(VARIABLE_kP, kP);}
void loadkP() {  loadVar(VARIABLE_kP);}

void readkI() {  readVar(VARIABLE_kI);}
void setkI() {  kI = float(kIval.getText()); setVarFloat(VARIABLE_kI, kI);}
void savekI() {  kI = float(kIval.getText()); saveVarFloat(VARIABLE_kI, kI);}
void loadkI() {  loadVar(VARIABLE_kI);}

void readkD() {  readVar(VARIABLE_kD);}
void setkD() {  kD = float(kDval.getText()); setVarFloat(VARIABLE_kD, kD);}
void savekD() {  kD = float(kDval.getText()); saveVarFloat(VARIABLE_kD, kD);}
void loadkD() {  loadVar(VARIABLE_kD);}
