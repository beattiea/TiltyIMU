import processing.serial.*;
import peasy.*;

PeasyCam cam;
Serial myPort;

int spheres = 1000;
float[] X = new float[100];
float[] Y = new float[100];
float[] Z = new float[100];

void setup() {
  size(displayWidth - 25, displayHeight - 50, P3D);
  cam = new PeasyCam(this, 2000);
  cam.setMinimumDistance(100);
  cam.setMaximumDistance(2500);
   
  background(0);
  
  smooth(8);
  
  noLoop();
  
  strokeWeight(10);
  
  println(Serial.list());
   
  myPort = new Serial(this, "/dev/tty.usbmodem16391", 115200);
  
  for (int i = 0; i < 100; i++) {
    X[i] = 0;
    Y[i] = 0;
    Z[i] = 0;
  }
}


void draw() {
  noStroke();
  lights();
  for (int i = 0; i < 100; i++) {
    
    translate(width / 2 + X[i] / 3, height / 2 + Y[i] / 3, Z[i] / 3);
    sphere(3);
  }
  //background(0);
  //rotateX(-.5);
  //rotateY(-.5);
}




String serial_event = null;
int data_count = 0;
Boolean new_x;
Boolean new_y;
Boolean new_z;
int counter = 0;

void serialEvent(Serial myPort) {
  serial_event = myPort.readStringUntil(10);
  if (serial_event != null) {
    if (serial_event.charAt(0) == 'X') {
      X[counter] = float(serial_event.substring(1));
      new_x = true;
    }
    if (serial_event.charAt(0) == 'Y') {
      Y[counter] = float(serial_event.substring(1));
      new_y = true;
    }
    if (serial_event.charAt(0) == 'Z') {
      Z[counter] = float(serial_event.substring(1));
      new_z = true;
    }
    
    if (new_x && new_y && new_z) {
      counter++;
      if (counter == 100) {  counter = 0;}
      new_x = false;
      new_y = false;
      new_z = false;
      //redraw();
    }
    //print(serial_event);
    
  }
}
