import controlP5.*;
import processing.serial.*;

ControlP5 cp5;
Serial myPort;

float kP, kI, kD;
float P=0, I=0, D=0;
float angle, angle_offset;
int P_val = 10;
int[] trim_pots = new int[4];
long start, stop = 0;
boolean connected = false;

/*
boolean sketchFullScreen() {
  return true;
}
*/

void setup() {
  cp5 = new ControlP5(this);
  smooth(8);
  size(displayWidth / 2, displayHeight / 2);
  
  setupGraphs();
  setupPIDtoggles(20, 50, 50);
  setupPIDsliders();
  setupPIDboxes(85, 50, 50);
  setupBangs(325, 50, 65);
  setupDropDowns();
  setupTextLabels();
  
  //refresh();
}

int count = 0;

int bR = 127, bG = 127, bB = 127;

void draw() {
  background(bR, bG, bB);
  pushMatrix();
  popMatrix();
  if (connected && (graphP.getState() || graphI.getState() || graphD.getState() || graphAngle.getState())) {
    PID_graph.draw();//  Needs to be made to darw only when data is being graphed
  }
}

String serial_event = null;

void serialEvent(Serial myPort) {
  while(myPort.available() >= 1) {
    serial_event = myPort.readStringUntil(10);
    //println(serial_event);
    switch (serial_event.charAt(0)) {
      case (VARIABLE_kP): {  kP = float(serial_event.substring(1));  kPval.setText(str(kP)); break;}
      case (VARIABLE_kI): {  kI = float(serial_event.substring(1));  kIval.setText(str(kI)); break;}
      case (VARIABLE_kD): {  kD = float(serial_event.substring(1));  kDval.setText(str(kD)); break;}
      
      case (VARIABLE_P): {  P = float(serial_event.substring(1)); P_label.setText("P: " + str(P)); break;}
      case (VARIABLE_I): {  I = float(serial_event.substring(1)); I_label.setText("I: " + str(I)); break;}
      case (VARIABLE_D): {  D = float(serial_event.substring(1)); D_label.setText("D: " + str(D)); break;}
      
      case (VARIABLE_ANGLE): {  angle = float(serial_event.substring(1)); angle_label.setText("Angle: " + str(angle)); break;}
      case (VARIABLE_OFFSET): {  angle_offset = float(serial_event.substring(1)); offsetVal.setText(str(angle_offset)); break;}
      
      case (CONFIRM): {  connected(); connected = true; break;}
      
      case (PING): {  myPort.write(CONFIRM);}
      
      case (VARIABLE_TRIM): {  setTrimVars(serial_event); break;}
      
      default: {  println(serial_event);}
    }
  }
}



void exit() {
  noLoop();
  if (myPort != null) {
    if (STREAM_PID) {  graphPID(false);}
    if (STREAM_P) {  graphP(false);}
    if (STREAM_I) {  graphI(false);}
    if (STREAM_D) {  graphD(false);}
    myPort.clear();
    myPort.stop();
  }
  println("Shutting down now...");
  super.exit();
}



void controlEvent(ControlEvent theEvent) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (theEvent.isGroup()) {
    // check if the Event was triggered from a ControlGroup
    if (theEvent.getGroup().getName() == "serialList") {
      if (myPort != null) {  myPort.clear();  myPort.stop();}
      try { 
        myPort = new Serial(this, serialList.item(int(serialList.getValue())).getName(), 115200);
        myPort.bufferUntil('\n');
        myPort.clear();
        myPort.write(PING);
        println("Serial started on: " + serialList.item(int(serialList.getValue())).getName());
      }
      catch (Exception e) {
        myPort.stop();
        println(e.getMessage() + " on: " + Serial.list()[int(theEvent.getGroup().getValue())]);
        serialStatus.setText("Not Connected: error (try refresh)")
                    .setColorValue(color(255, 0, 0));
      }
    }
  }
}
