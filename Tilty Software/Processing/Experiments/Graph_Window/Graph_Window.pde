import java.awt.Frame;
import java.awt.BorderLayout;
import controlP5.*;

private ControlP5 cp5;

ControlFrame cf;

Frame f;

int def;

void setup() {
  size(400, 400);
  cp5 = new ControlP5(this);
  
  //cp5.addButton("CloseGraph", 1);
  cp5.addButton("OpenGraph", 1);
  
  // by calling function addControlFrame() a
  // new frame is created and an instance of class
  // ControlFrame is instanziated.
  cf = addControlFrame("extra", 600,300);
  
  // add Controllers to the 'extra' Frame inside 
  // the ControlFrame class setup() method below.
}

void draw() {
  background(def);
  
  textAlign(CENTER);
  textSize(32);
  fill(255);
  text("Hello World", 200, 200);
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
  f.setTitle(theName);
  f.setSize(p.w, p.h);
  f.setLocation(100, 100);
  f.setResizable(true);
  //f.setUndecorated(true);
  f.setVisible(true);
  return p;
}
