import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import saito.objloader.*; 
import processing.serial.*; 
import java.awt.Frame; 
import java.awt.BorderLayout; 
import controlP5.*; 
import org.gwoptics.graphics.graph2D.Graph2D; 
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation; 
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace; 
import java.nio.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class TiltyIMU_Demo extends PApplet {








//import processing.opengl.*;

private ControlP5 gui;

OBJModel TiltyIMU;

ControlFrame cf;
Frame f;

int x_size = 1024;
int y_size = x_size * 10/16;
float scale = x_size / 320;

PFont font = createFont("Arial", 18, true);
PFont globalFont = createFont("Arial", 12, true);
ControlFont tabFont = new ControlFont(font, 18);
ControlFont global = new ControlFont(globalFont, 12);

public void setup() {
  if (y_size >= displayHeight) {  y_size = displayHeight - 20;}
  size(x_size, y_size, P3D);
  noStroke();
  smooth(4);
  
  /*//  3D Model code, but the model needs work
  TiltyIMU = new OBJModel(this, "Tilty.obj", "absolute", TRIANGLES);
  TiltyIMU.scale(5);
  TiltyIMU.translateToCenter();
  */
  
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

float batt_voltage = 13.2f;
float min_batt = 5.3f;//  Can't be less than 5.16 volts due to regulator drop out
float max_batt = 24;//  Can't be more than 51.8 volts or it will damage the Teensy;void draw() {
public void draw() {
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


public void controlEvent(ControlEvent event) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (event.isGroup()) {
    if (event.getGroup().toString().equals("serial [DropdownList]")) {  serialSetup(PApplet.parseInt(event.getValue()));}
  }
  
  else if (event.isController()) {
    println("event from controller : "+event.getController().getValue()+" from "+event.getController());
  }
}




public void resizeGUI() {
  x_size = width;
  y_size = x_size * 10/16;
  scale = x_size / 320;
  frame.setSize(x_size, y_size);
  resize(x_size, y_size);
}



public void CloseGraph(int theValue) {
  f.setVisible(false);
}

public void OpenGraph() {
  f.setVisible(true);
}

public ControlFrame addControlFrame(String theName, int theWidth, int theHeight) {
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

public void exit() {
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




/*
********************************
Might be better off implementing graph in ControlP5
********************************
*/


public class ControlFrame extends PApplet {

  int w, h;

  int abc = 100;
  
  class eq implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      return mouseX;
    }    
  }
  
  class eq2 implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      return mouseY;
    }    
  }
  
  class eq3 implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      if(mousePressed)
        return 400;
      else
        return 0;
    }    
  }

RollingLine2DTrace r,r2,r3;
Graph2D g;
Graph2D gp;
  
  public void setup() {
    size(600,300);
    
    frameRate(50);
    
    r3 = new RollingLine2DTrace(new eq3(),20,0.02f);
    r3.setTraceColour(0, 0, 255);
     
    g = new Graph2D(this, (width / 3) * 2, (height / 3) * 2, false);
    g.setYAxisMax(width);
    //g.addTrace(r);
    //g.addTrace(r2);
    g.addTrace(r3);
    g.position.y = 10;
    g.position.x = 125;
    g.setYAxisTickSpacing(100);
    g.setXAxisMax(5f);
    
    gui = new ControlP5(this);
    gui.addButton("CloseGraph", 1);
    gui.addToggle("X", false);
    gui.addToggle("Y", false);
  }
  
  public void CloseGraph(int theValue) {
    f.setVisible(false);
  }
  
  public void X (boolean toggle) {
    if (toggle) {
      r  = new RollingLine2DTrace(new eq() ,20,0.02f);
      r.setTraceColour(0, 255, 0);
      g.addTrace(r);
    }
    else {
      g.removeTrace(r);
    }
  }
  
  public void Y (boolean toggle) {
    if (toggle) {
      r2 = new RollingLine2DTrace(new eq2(),20,0.02f);
      r2.setTraceColour(255, 0, 0);
      g.addTrace(r2);
    }
    else {
      g.removeTrace(r2);
    }
  }

boolean paused = false;

  public void draw() {
      background(abc);
      g.draw();
  }
  
  public void keyPressed() {
    if (keyCode == TAB) {
      paused = !paused;
      println("Paused: " + paused);
    }
  }
//  private ControlFrame() {
//  }

  public ControlFrame(Object theParent, int theWidth, int theHeight) {
    parent = theParent;
    w = theWidth;
    h = theHeight;
  }


  public ControlP5 control() {
    return gui;
  }
  
  
  ControlP5 gui;

  Object parent;

  
}
Serial myPort = null;

long connected = 0;
int timeout = 5000;

final char YAW = 'Y';
final char PITCH = 'P';
final char ROLL = 'R';
final char BATT = 'V';
final char ALT = 'A';
final char TEMP = 'T';
final char HEADING = 'H';


public void serialSetup(int comm_port) {
  if (comm_port == -1) {  serialTest(); return;}
  if (comm_port == -2) {
    serial_conn.clear();
    serial_conn.addItem("Refresh list", -2);
    serial_conn.addItems(Serial.list());
    serial_conn.addItem("Attempt to auto-connect", -1);
    return;
  }
  try {
    if (myPort != null) {  myPort.stop();}
    myPort = new Serial(this, Serial.list()[comm_port], 115200);
    myPort.clear();
    myPort.bufferUntil('\n');
    println("Serial started on: " + Serial.list()[comm_port]);
    myPort.write(0);
    myPort.write(0);
    myPort.write(0);
    myPort.write('B');
  }
  catch (Exception serialException) {
    myPort = null;
    println("Not Connected to: " + Serial.list()[comm_port]);
  }
}


public void serialEvent(Serial myPort) {
  String serial_data;
  try {
    while (myPort.available() != 0) {
      connected = millis();
      serial_data = new String(myPort.readBytesUntil('\n'));
      //serial_data = "l123";
      
      switch (serial_data.charAt(0)) {
        case (ROLL): {  roll = PApplet.parseFloat(serial_data.substring(1)); break;}
        case (PITCH): {  pitch = PApplet.parseFloat(serial_data.substring(1)); break;}
        case (YAW): {  yaw = -PApplet.parseFloat(serial_data.substring(1)); break;}
        case (BATT): {  batt_voltage = PApplet.parseFloat(serial_data.substring(1)); break;}
        case (ALT): {  altitude = PApplet.parseFloat(serial_data.substring(1)); break;}
        case (TEMP): {  temperature = PApplet.parseFloat(serial_data.substring(1)); break;}
        //case (HEADING): {  temperature = float(serial_data.substring(1)); break;}
        case('\n'): {break;}
        //default: {  println(serial_data); break;}
      }
    }
  }
  catch (Exception serialException) {
    println("SerialEvent error!");
  }
}


public void checkConn() {
  if (millis() - connected > timeout || millis() < timeout) {
    connected = 0;
    serial_conn.setColorBackground(color(219,39,22))
               .setLabel("Select Serial Port")
               ;
    //myPort = null;
  }
  else {
    serial_conn.setColorBackground(color(2,198,23))
               .setLabel("Connected")
               ;
  }
}

public void serialTest() {
  for (int i = Serial.list().length - 1; i >= 0 && connected == 0; i--) {
    try {
      myPort = new Serial(this, Serial.list()[i], 115200);
      myPort.bufferUntil('\n');
      println("Serial started on: " + Serial.list()[i]);
      
      myPort.write('|');
      long start = millis();
      while (millis() - start < timeout && connected == 0) {
        delay(1);
      }
    }
    catch (Exception serialException) {
      println("Not Connected to: " + Serial.list()[i]);
      myPort = null;
    }
  }
}



public static byte [] float2ByteArray (float value)
{  
     return ByteBuffer.allocate(4).putFloat(value).array();
}

public static float byteArray2Float(byte[] value)
{
   if(value.length == 4)
  {
     return ByteBuffer.wrap(value).order(ByteOrder.BIG_ENDIAN).getFloat();
  }
  else return -1;
}


public void setupSystemTab() {
  int background = color(90, 90, 90);
  int label = color(255);
  int active = color(137, 137, 137);
  
  gui.addTab("System")
     .setLabel("Tilty Configuration")
     .setColorBackground(background)
     .setColorLabel(label)
     .setColorActive(active)
     .getCaptionLabel().setFont(tabFont)
     ;
     
}

public void drawSystem() {
  
}
Textlabel yaw_label, pitch_label, roll_label, batt_label, alt_label, temp_label;
DropdownList serial_conn;

public void setupTelemetryTab() {
  int background = color(100, 100, 100);
  int Label = color(255);
  int active = color(127, 127, 127);
  
  
  gui.getTab("default")
     .setLabel("Main")
     .setColorBackground(background)
     .setColorLabel(Label)
     .setColorActive(active)
     .getCaptionLabel().setFont(tabFont)
     ;
     
  serial_conn = gui.addDropdownList("serial")
                   .setPosition(PApplet.parseInt(2*scale), PApplet.parseInt(13*scale))
                   .setSize(PApplet.parseInt(75*scale), PApplet.parseInt(100*scale))
                   .setBarHeight(PApplet.parseInt(6*scale))
                   .setScrollbarVisible(true)
                   .addItems(Serial.list())
                   .setLabel("Select Serial Port")
                   .setColorActive(0)
                   .setColorForeground(color(200,25,25))
                   ;
  serial_conn.captionLabel().style().marginTop = serial_conn.getBarHeight() / 2 - 6;
  serial_conn.addItem("Attempt to auto-connect", -1);
  serial_conn.addItem("Refresh list", -2);
                
  
  yaw_label = gui.addTextlabel("yawLabel")
                 .setText("Yaw: " + str(yaw))
                 .setPosition(width/2 - PApplet.parseInt(16*scale), PApplet.parseInt(150*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  pitch_label = gui.addTextlabel("pitchLabel")
                 .setText("Pitch: " + str(pitch))
                 .setPosition(width/2 - PApplet.parseInt(16*scale), PApplet.parseInt(155*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  roll_label = gui.addTextlabel("rollLabel")
                 .setText("Roll: " + str(roll))
                 .setPosition(width/2 - PApplet.parseInt(16*scale), PApplet.parseInt(160*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
  
  alt_label = gui.addTextlabel("altLabel")
                 .setText("Altitude: " + str(altitude))
                 .setPosition(width/2 - PApplet.parseInt(16*scale), PApplet.parseInt(165*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  temp_label = gui.addTextlabel("tempLabel")
                 .setText("Temperature: " + str(temperature))
                 .setPosition(width/2 - PApplet.parseInt(16*scale), PApplet.parseInt(170*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
  
  batt_label = gui.addTextlabel("battLabel")
                  .setText("Voltage: " + str(batt_voltage))
                  .setPosition(width - PApplet.parseInt(30*scale), PApplet.parseInt(2*scale))
                  .setColor(255)
                  .setFont(tabFont);
                  ;
                  
  gui.addButton("zero", 1)
     .setSize(93, 20)
     .setLabel("Zero Angles")
     .setPosition(width/2 - 46, PApplet.parseInt(178*scale))
     ;
}


public void drawTelemetry() {
  if (gui.getTab("default").isActive()) {
    yaw_label.setText("Yaw: " + nfs(yaw, 3, 2) + "\u00b0");
    pitch_label.setText("Pitch: " + nfs(pitch, 2, 2) + "\u00b0");
    roll_label.setText("Roll: " + nfs(roll, 2, 2) + "\u00b0");
    batt_label.setText("Voltage:\n" + nfs(batt_voltage, 1, 2) + "v");
    if (!Float.isNaN(altitude)) {  alt_label.setText("Altitude: " + nfs(altitude, 3, 2) + " m");}
    else {  alt_label.setText("Altitude: Not detected");}
    if (!Float.isNaN(temperature)) {  temp_label.setText("Temperature: " + nfs(temperature, 2, 2) + "\u00b0C");}
    else {  temp_label.setText("Temperature: Not detected");}
    
    //  Battery voltage Meter 
    pushMatrix();
    stroke(255);
    fill(10);
    rect(width - 5*scale, 25*scale, 10, -24 * scale);
    noStroke();
    if (batt_voltage > min_batt) {  fill(0, 255, 0);}
    else {  fill(255, 0, 0);}
    rect(width - 5*scale, 25*scale, 10, constrain(-map(batt_voltage, 0, max_batt, 0, 24*scale), -24*scale, 0));
    popMatrix();
  }
}

public void zero(int value) {
  if (myPort != null) {
    println("Zeroed!");
    myPort.write('Z');
    myPort.write('Y');
    myPort.write('P');
    myPort.write('Z');
    myPort.write('A');
  }
}
String file_path;
String file_name;

public void setupFirmwareTest() {
  gui.addButton("update", 2)
     .setSize(120, 20)
     .setLabel("Update Firmware")
     .setPosition(width / 2 - 60, PApplet.parseInt(120*scale))
     ;
     
     gui.getController("update").moveTo("System");
}

public void chooseNewFirmware() {
  selectInput("Select a new .hex file", "fileSelected");
}

public void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    file_path = selection.getAbsolutePath();
    //file_name = file_path.substring(0, file_path.length() - 4);
    file_name = selection.getName().substring(0, selection.getName().length() - 4);
    file_path = selection.getParent();
    uploadFirmware();
  }
}

public void update() {
  chooseNewFirmware();
}

public void uploadFirmware() {
  println("Path: " + file_path);
  println("Name: " + file_name);
  String[] command_line = {dataPath("") + "/tools/teensy_post_compile", "-file=" + file_name + "", "-path=" + file_path, "-tools=" + dataPath("tools")};
  for (int i = 0; i < 4; i++) {
    print(command_line[i] + " ");
  }
  exec(command_line);
  String[] command_line2 = {dataPath("") + "/tools/teensy_reboot", "-pmk20dx128", "-chalfkay"};
  exec(command_line2);
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "TiltyIMU_Demo" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
