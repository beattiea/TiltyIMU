import processing.serial.*;

import java.awt.Frame;
import java.awt.BorderLayout;
import controlP5.*;

private ControlP5 gui;

ControlFrame cf;
Frame f;

int x_size = 1024;
int y_size = x_size * 10/16;
float scale = x_size / 320;

PFont font = createFont("Arial", 18, true);
PFont globalFont = createFont("Arial", 12, true);
ControlFont tabFont = new ControlFont(font, 18);
ControlFont global = new ControlFont(globalFont, 12);

void setup() {
  if (y_size >= displayHeight) {  y_size = displayHeight - 20;}
  size(x_size, y_size, P3D);
  noStroke();
  smooth(4);
  
  frame.setTitle("Tilty Control");
  //frame.setLocation(displayWidth / 2 - width / 2, displayHeight / 2 - height / 2);
  //frame.setResizable(true);
  
  gui = new ControlP5(this);
  gui.setControlFont(global);
  
  setupTelemetryTab();
  setupSystemTab();
  
  //gui.addButton("CloseGraph", 1);
  //gui.addButton("OpenGraph", 1);
  
  // by calling function addControlFrame() a
  // new frame is created and an instance of class
  // ControlFrame is instanziated.
  //cf = addControlFrame("extra", 600 ,300);              CURRENTLY BROKEN
  
  // add Controllers to the 'extra' Frame inside 
  // the ControlFrame class setup() method below.
  
  setupFirmwareTest();
}

float t = 0;
float yaw, pitch, roll, altitude, temperature;

float batt_voltage = 13.2;
float min_batt = 5.3;//  Can't be less than 5.16 volts due to regulator drop out
float max_batt = 24;//  Can't be more than 51.8 volts or it will damage the Teensy;void draw() {
void draw() {
  background(10);
  
  //yaw = map(mouseX, 0, width, 0, 360) - 180;
  //pitch = map(mouseY, 0, height, 0, 360) + - 180;
  //if (mousePressed) {  roll = map(mouseX, 0, width, 0, 360) - 180;}
  drawTelemetry();
  drawSystem();
  
  checkConn();
  
  pushMatrix();
  translate(width/2, height/2);
  rotateY(-radians(yaw));
  rotateX(-radians(pitch));
  rotateZ(-radians(roll));
  lights();
  fill(149,2,135);
  box(height / 5, height / 16, height / 3);
  //TiltyIMU.draw();
  popMatrix();
  noLights();
  
  if (width != x_size || height != y_size) {
    resizeGUI();
  }
  
  //println(frameRate);
}


void controlEvent(ControlEvent event) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (event.isGroup()) {
    if (event.getGroup().toString().equals("serial [DropdownList]")) {  serialSetup(int(event.getValue()));}
  }
  
  else if (event.isController()) {
    println("event from controller : "+event.getController().getValue()+" from "+event.getController());
  }
}




void resizeGUI() {
  x_size = width;
  y_size = x_size * 10/16;
  scale = x_size / 320;
  frame.setSize(x_size, y_size);
  resize(x_size, y_size);
}



void CloseGraph(int theValue) {
  f.setVisible(false);
}

void OpenGraph() {
  f.setVisible(true);
}

ControlFrame addControlFrame(String theName, int theWidth, int theHeight) {
  f = new Frame(theName);
  ControlFrame p = new ControlFrame(this, theWidth, theHeight);
  f.add(p);
  p.init();
  f.setVisible(true);
  f.setTitle(theName);
  f.setSize(p.w, p.h);
  f.setLocation(100, 100);
  f.setResizable(true);
  //f.setUndecorated(true);
  f.setVisible(false);
  
  return p;
}

void exit() {
  println("Quitting...");
  if (myPort != null) {
    try {
      myPort.stop();
    }
    catch (Exception serialException) {
      println("Serial stop exception!");
      myPort = null;
    }
  }
  println("I quit!");
  System.exit(0);
}
