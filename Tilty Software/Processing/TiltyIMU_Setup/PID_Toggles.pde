void setupPIDtoggles(int x, int y, int spacing) {
  setupPtoggle(x, y);
  setupItoggle(x, y + spacing);
  setupDtoggle(x, y + spacing * 2);
  
  setupGraphP(x, 200);
  setupGraphI(x + 55, 200);
  setupGraphD(x + 110, 200);
  setupGraphPID(x + 165, 200);
  
  setupGraphAngle(x + 220, 200);
}

boolean PEnabled = false;
boolean IEnabled = false;
boolean DEnabled = false;

Toggle graphP, graphI, graphD, graphPID, graphAngle;

void setupPtoggle(int x, int y) {
  cp5.addToggle("PEnable")
     .setPosition(x, y)
     .setSize(50, 20)
     .setState(true)
     .setColorActive(color(0,255,0))
     .setColorBackground(color(255,0,0))
     .setLabelVisible(true)
     .setCaptionLabel("P Enable")
     .getCaptionLabel().setFont(createFont("arial", 10))
     ;
}

void setupItoggle(int x, int y) {
  cp5.addToggle("IEnable")
     .setPosition(x, y)
     .setSize(50, 20)
     .setState(true)
     .setColorActive(color(0,255,0))
     .setColorBackground(color(255,0,0))
     .setLabelVisible(true)
     .setCaptionLabel("I Enable")
     .getCaptionLabel().setFont(createFont("arial", 10))
     ;
}

void setupDtoggle(int x, int y) {
  cp5.addToggle("DEnable")
     .setPosition(x, y)
     .setSize(50, 20)
     .setState(true)
     .setColorActive(color(0,255,0))
     .setColorBackground(color(255,0,0))
     .setLabelVisible(true)
     .setCaptionLabel("D Enable")
     .getCaptionLabel().setFont(createFont("arial", 10))
     ;
}



void setupGraphP(int x, int y) {
  graphP = cp5.addToggle("graphP")
              .setPosition(x, y)
              .setSize(50, 20)
              .setState(false)
              .setColorActive(color(0,255,0))
              .setColorBackground(color(50,50,50));
              
  graphP.setLabelVisible(true)
        .setCaptionLabel("Graph P")
        .getCaptionLabel().setFont(createFont("arial", 10))
        .align(CENTER, CENTER)
        .setColor(color(127,127,127))
        ;
}

void setupGraphI(int x, int y) {
  graphI = cp5.addToggle("graphI")
              .setPosition(x, y)
              .setSize(50, 20)
              .setState(false)
              .setColorActive(color(255,0,0))
              .setColorBackground(color(50,50,50));
              
  graphI.setLabelVisible(true)
        .setCaptionLabel("Graph I")
        .getCaptionLabel().setFont(createFont("arial", 10))
        .align(CENTER, CENTER)
        .setColor(color(127,127,127))
        ;
}

void setupGraphD(int x, int y) {
  graphD = cp5.addToggle("graphD")
              .setPosition(x, y)
              .setSize(50, 20)
              .setState(false)
              .setColorActive(color(0,0,255))
              .setColorBackground(color(50,50,50));
              
  graphD.setLabelVisible(true)
        .setCaptionLabel("Graph D")
        .getCaptionLabel().setFont(createFont("arial", 10))
        .align(CENTER, CENTER)
        .setColor(color(127,127,127))
        ;
}

void setupGraphPID(int x, int y) {
  graphPID = cp5.addToggle("graphPID")
                .setPosition(x, y)
                .setSize(50, 20)
                .setState(false)
                .setColorActive(color(255,255,255))
                .setColorBackground(color(50,50,50));
              
  graphPID.setLabelVisible(true)
          .setCaptionLabel("PID")
          .getCaptionLabel().setFont(createFont("arial", 10))
          .align(CENTER, CENTER)
          .setColor(color(127,127,127))
          ;
}

void setupGraphAngle(int x, int y) {
  graphAngle = cp5.addToggle("graphAngle")
                .setPosition(x, y)
                .setSize(50, 20)
                .setState(false)
                .setColorActive(color(0,0,0))
                .setColorBackground(color(50,50,50));
              
  graphAngle.setLabelVisible(true)
          .setCaptionLabel("Tilt")
          .getCaptionLabel().setFont(createFont("arial", 10))
          .align(CENTER, CENTER)
          .setColor(color(127,127,127))
          ;
}




//  Functions that are called when a toggle is clicked  //
void graphP(boolean value) {//  Needs to be updated to check streaming status and update accordingly
  if (myPort != null) {
    myPort.write(STREAM);
    myPort.write(VARIABLE_P);
    STREAM_P = value;
    if (value) {
      myPort.write(TRUE);
      P_line = new RollingLine2DTrace(new P_eq(), update_freq, (update_freq / 100.0) * 0.1);
      P_line.setTraceColour(0, 255, 0);
      PID_graph.addTrace(P_line);
      //P_line.setTraceColour(0,255,0);
    }
    if (!value) {
      myPort.write(FALSE);
      PID_graph.removeTrace(P_line);
      //P_line.setTraceColour(bR, bG, bB);
    }
  }
}

void graphI(boolean value) {//  Needs to be updated to check streaming status and update accordingly
  if (myPort != null) {
    myPort.write(STREAM);
    myPort.write(VARIABLE_I);
    STREAM_I = value;
    if (value) {
      myPort.write(TRUE);
      I_line = new RollingLine2DTrace(new I_eq(), update_freq, (update_freq / 100.0) * 0.1);
      I_line.setTraceColour(255, 0, 0);
      PID_graph.addTrace(I_line);
    }
    if (!value) {
      myPort.write(FALSE);
      PID_graph.removeTrace(I_line);
    }
  }
}

void graphD(boolean value) {//  Needs to be updated to check streaming status and update accordingly
  if (myPort != null) {
    myPort.write(STREAM);
    myPort.write(VARIABLE_D);
    STREAM_D = value;
    if (value) {
      myPort.write(TRUE);
      D_line = new RollingLine2DTrace(new D_eq(), update_freq, (update_freq / 100.0) * 0.1);
      D_line.setTraceColour(0, 0, 255);
      PID_graph.addTrace(D_line);
    }
    if (!value) {
      myPort.write(FALSE);
      PID_graph.removeTrace(I_line);
    }
  }
}

void graphPID(boolean value) {//  Needs to be updated to check streaming status and update other toggles accordingly
  if (myPort != null) {
    if (value) {
      if (!STREAM_P) {  myPort.write(STREAM);  myPort.write(VARIABLE_P); myPort.write(TRUE); graphP.setState(true);}
      if (!STREAM_I) {  myPort.write(STREAM);  myPort.write(VARIABLE_I); myPort.write(TRUE); graphI.setState(true);}
      if (!STREAM_D) {  myPort.write(STREAM);  myPort.write(VARIABLE_D); myPort.write(TRUE); graphD.setState(true);}
      PID_line = new RollingLine2DTrace(new Power_eq(), update_freq, (update_freq / 100.0) * 0.1);
      PID_line.setTraceColour(255, 255, 255);
      PID_graph.addTrace(PID_line);
    }
    if (!value) {
      if (STREAM_P) {  myPort.write(STREAM);  myPort.write(VARIABLE_P); myPort.write(FALSE); graphP.setState(false);}
      if (STREAM_I) {  myPort.write(STREAM);  myPort.write(VARIABLE_I); myPort.write(FALSE); graphI.setState(false);}
      if (STREAM_D) {  myPort.write(STREAM);  myPort.write(VARIABLE_D); myPort.write(FALSE); graphD.setState(false);}
      PID_graph.removeTrace(PID_line);
    }
    STREAM_PID = value;
  }
}

void graphAngle(boolean value) {//  Needs to be updated to check streaming status and update accordingly
  if (myPort != null) {
    myPort.write(STREAM);
    myPort.write(VARIABLE_ANGLE);
    STREAM_ANGLE = value;
    if (value) {
      myPort.write(TRUE);
      Angle_line = new RollingLine2DTrace(new Angle_eq(), update_freq, (update_freq / 100.0) * 0.1);
      Angle_line.setTraceColour(0, 0, 0);
      PID_graph.addTrace(Angle_line);
    }
    if (!value) {
      myPort.write(FALSE);
      PID_graph.removeTrace(Angle_line);
    }
  }
}

void PEnable(boolean value) {
  PEnabled = value;
  if (myPort != null) {
    if (value) {
      myPort.write(SET);
      myPort.write(VARIABLE_kP);
      myPort.write(str(kP));
      kPval.setText(str(kP));
      //serialStatus.setText("kP enabled");
    }
    
    else {
      myPort.write(SET);
      myPort.write(VARIABLE_kP);
      myPort.write(str(0.0));
      kPval.setText(str(0.0));
      //serialStatus.setText("kP disabled");
    }
  }
}

void IEnable(boolean value) {
  IEnabled = value;
  if (myPort != null) {
    if (value) {
      myPort.write(SET);
      myPort.write(VARIABLE_kI);
      myPort.write(str(kI));
      kIval.setText(str(kI));
      //serialStatus.setText("kI enabled");
    }
    
    else {
      myPort.write(SET);
      myPort.write(VARIABLE_kI);
      myPort.write(str(0.0));
      kIval.setText(str(0.0));
      //serialStatus.setText("kI disabled");
    }
  }
}

void DEnable(boolean value) {
  DEnabled = value;
  if (myPort != null) {
    if (value) {
      myPort.write(SET);
      myPort.write(VARIABLE_kD);
      myPort.write(str(kD));
      kDval.setText(str(kD));
      //serialStatus.setText("kD enabled");
    }
    
    else {
      myPort.write(SET);
      myPort.write(VARIABLE_kD);
      myPort.write(str(0.0));
      kDval.setText(str(0.0));
      serialStatus.setText("kD disabled");
    }
  }
}
