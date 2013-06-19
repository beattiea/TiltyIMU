Textfield kPval, kIval, kDval, offsetVal;

void setupPIDboxes(int x, int y, int spacing) {
  setPbox(x, y);
  setIbox(x, y + spacing);
  setDbox(x, y + spacing * 2);
  setOffsetBox(x, 225);
}

void setPbox(int x, int y) {
  kPval = cp5.addTextfield("kPval")
             .setPosition(x, y)
             .setSize(100, 20)
             .setFocus(true)
             .keepFocus(false)
             .setAutoClear(false)
             ;
     
  kPval.setCaptionLabel("kP Value")
       .setFont(createFont("arial", 14.0))
       .getCaptionLabel().setFont(createFont("arial", 10))
       ;
}

void setIbox(int x, int y) {
  kIval = cp5.addTextfield("kIval")
             .setPosition(x, y)
             .setSize(100, 20)
     //.setFocus(true)
     .setAutoClear(false)
     ;
     
  kIval.setCaptionLabel("kI Value")
       .setFont(createFont("arial", 14.0))
       .getCaptionLabel().setFont(createFont("arial", 10))
       ;
}

void setDbox(int x, int y) {
  kDval = cp5.addTextfield("kDval")
             .setPosition(x, y)
             .setSize(100, 20)
             //.setFocus(true)
             .setAutoClear(false)
             ;
     
  kDval.setCaptionLabel("kD Value")
       .setFont(createFont("arial", 14.0))
       .getCaptionLabel().setFont(createFont("arial", 10))
       ;
}

void setOffsetBox(int x, int y) {
  offsetVal = cp5.addTextfield("offsetVal")
                 .setPosition(x, y)
                 .setSize(100, 20)
                 //.setFocus(true)
                 .setAutoClear(false)
                 ;
     
  offsetVal.setCaptionLabel("Angle Offset")
           .setFont(createFont("arial", 14.0))
           .getCaptionLabel().setFont(createFont("arial", 10))
           ;
}



void kPval(String value) {
  kP = float(value);
  cp5.get(Toggle.class,"PEnable").setState(true);
  setVarFloat(VARIABLE_kP, kP);
  serialStatus.setText("Set kP value");
}

void kIval(String value) {
  kI = float(value);
  cp5.get(Toggle.class,"IEnable").setState(true);
  setVarFloat(VARIABLE_kI, kI);
  serialStatus.setText("Set kI value");
}

void kDval(String value) {
  kD = float(value);
  cp5.get(Toggle.class,"DEnable").setState(true);
  setVarFloat(VARIABLE_kD, kD);
  serialStatus.setText("Set kD value");
}

void offsetVal(String value) {
  angle_offset = float(value);
  setVarFloat(VARIABLE_OFFSET, angle_offset);
  serialStatus.setText("Set angle offset");
}
