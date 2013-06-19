Textlabel serialStatus, P_label, I_label, D_label, angle_label;

void setupTextLabels() {
  setupSerialStatus(230, 0);
  
  setupPlabel(575, 53);
  setupIlabel(575, 103);
  setupDlabel(575, 153);
  setupAngleLabel(675, 103);
}

void setupSerialStatus(int x, int y) {
  serialStatus = cp5.addTextlabel("serialConnected")
                    .setText("Not Connected")
                    .setPosition(x, y)
                    .setColorValue(color(255, 0, 0))
                    .setFont(createFont("arial", 20))
                    ;
}

void setupPlabel(int x, int y) {
  P_label = cp5.addTextlabel("Plabel")
               .setText("P: Not reading")
               .setPosition(x, y)
               .setColorValue(color(0, 255, 0))
               .setFont(createFont("arial", 14))
               ;
}

void setupIlabel(int x, int y) {
  I_label = cp5.addTextlabel("Ilabel")
               .setText("I: Not reading")
               .setPosition(x, y)
               .setColorValue(color(255, 0, 0))
               .setFont(createFont("arial", 14))
               ;
}

void setupDlabel(int x, int y) {
  D_label = cp5.addTextlabel("Dlabel")
               .setText("D: Not reading")
               .setPosition(x, y)
               .setColorValue(color(0, 0, 255))
               .setFont(createFont("arial", 14))
               ;
}

void setupAngleLabel(int x, int y) {
  angle_label = cp5.addTextlabel("angleLabel")
                   .setText("Angle: Not reading")
                   .setPosition(x, y)
                   .setColorValue(color(0, 0, 0))
                   .setFont(createFont("arial", 14))
               ;
}
