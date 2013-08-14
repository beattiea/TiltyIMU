/*
Processing tool for collecting and viewing points
magn calibration functions 01

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  3DScatter v1.1 - June 2012, by Hon Bo Xuan
*/

import processing.opengl.*;
import processing.serial.*;
import java.awt.event.*;

Serial port;
static int totcount = 5000;
static String serialport = "/dev/tty.usbmodem12341";
static int serialbaud = 115200;
static String filename = "../magnpoints.txt";

static float zoom = 0.3;

PFont font;
int count = 0;
int[] vals = new int[3];
int[] valsold = new int[3];

PVector[] vecs = new PVector[totcount];

int x_max = 0, x_min = 0, y_max = 0, y_min = 0, z_max = 0, z_min = 0;
int x_length = 0, y_length = 0, z_length = 0;
float length_mean = 0;
float x_gain = 1, y_gain = 1, z_gain = 1;
int spheredim = 0;


/*
write output file, setup output format here
*/
void writeData() {
  PrintWriter output = createWriter(filename); 
  for (int i = 0; i < count; i++) {
    PVector v = vecs[i];
      output.println(v.x + "\t" + v.y + "\t" + v.z);
  }
  output.flush();
  output.close();
}

void setup() {
  size(700, 700, P3D);
  frame.addMouseWheelListener(new MouseWheelInput());
  font = createFont("ArialMT", 32, true);
  port = new Serial(this, serialport, serialbaud); 
  port.bufferUntil(10);
  port.write(0x22);
}

/*
main loop draw
*/
void draw() {
  //readfromserial();
  
  background(0);  
  translate(width/2, height/2);
    
  //print text
  textFont(font, 20);
  fill(255, 255, 255);
  text("Gain: " + x_gain + ", " + y_gain + ", " + z_gain, -width/2 + 20, height/2 - 20);
  text("Count: " + count + " / " + totcount, -width/2 + 20, height/2 - 50);
  
  //rotate plan
  float z = radians(0.5 * mouseX);
  float r = -0.001 * (mouseY - 500);
  rotateY(z);
  rotateX(r * cos(z));
  rotateZ(r * sin(z));
    
  //scale zoom
  scale(zoom, -zoom, zoom);
    
  //print box
  noFill();
  stroke(100);
  strokeWeight(1);
  box(1200);
  
  //print axis-X
  stroke(255, 0, 0);
  strokeWeight(2);
  line (300, 0, 0, 275, 0, 25);
  line (300, 0, 0, 275, 0, -25); 
  line (320, -20, 0, 340, 20, 0);
  line (320, 20, 0, 340, -20, 0);
  line(-300, 0, 0, 300, 0, 0);
  
  //print axis-Y
  stroke(0, 0, 255);
  strokeWeight(2);
  line (0, 0, 300, 25, 0, 275);
  line (0, 0, 300, -25, 0, 275); 
  line (0, 20, 320, 0, 0, 330);
  line (0, 0, 330, 0, 20, 340);
  line (0, 0, 330, 0, -20, 330);
  line(0, 0, -300, 0, 0, 300);
  
  //print axis-Z
  stroke(0, 255, 0);
  strokeWeight(2);
  line (0, 300, 0, 25, 275, 0);
  line (0, 300, 0, -25, 275, 0);
  line (-10, 350, 0, 10, 350, 0);
  line (10, 350, 0, -10, 320, 0); 
  line (-10, 320, 0, 10, 320, 0); 
  line(0, -300, 0, 0, 300, 0);
  
  //print sphere
  noFill();
  stroke(255, 30);
  sphere(spheredim);
  
  //print points
  for (int i = 0; i < count; i++) {
    PVector v = vecs[i];
    stroke(255);
    strokeWeight(3);
    point(v.x, v.y, v.z);
  }
}

/*
find gain
*/
void findGain() {
  x_length = x_max - x_min;
  y_length = y_max - y_min;
  z_length = z_max - z_min;
  length_mean = (x_length + y_length + z_length) / 3;
  x_gain = x_length / length_mean;
  y_gain = y_length / length_mean;
  z_gain = z_length / length_mean;
}


/*
find spheredim
*/
void findSpheredim() {
  if(x_max > spheredim)
    spheredim = x_max;
  if(y_max > spheredim)
    spheredim = y_max;
  if(z_max > spheredim)
    spheredim = z_max;
}

/*
mouse zoom
*/
class MouseWheelInput implements MouseWheelListener{
  void mouseWheelMoved(MouseWheelEvent e) {
    zoom -= 0.05 * e.getWheelRotation();
    zoom = constrain(zoom, 0.2, 2);
  }
}

/*
get serial data
*/
void serialEvent(Serial port) {
  port.write(0x22);
  byte[] buf = new byte[128];
  int bufread = port.readBytesUntil((byte)10, buf);
  //println(bufread);
  //println(buf);
  if(bufread > 0) {
    if(count < vecs.length) {
      vals[0] = (short)((buf[1] & 0xff)<<8 | (buf[0] & 0xff));
      vals[1] = (short)((buf[3] & 0xff)<<8 | (buf[2] & 0xff));
      vals[2] = (short)((buf[5] & 0xff)<<8 | (buf[4] & 0xff));
      for (int i = 0; i < 3; i++) {
        //println(vals[i]);
      }
      if(vals[0] != valsold[0] && vals[1] != valsold[1] && vals[2] != valsold[2]) { //collect only new points
        valsold[0] = vals[0];
        valsold[1] = vals[1];
        valsold[2] = vals[2];
        vecs[count] = new PVector(vals[0], vals[1], vals[2]);
        if(vals[0] > x_max)
           x_max = vals[0];
           println(x_max);
        if(vals[1] > y_max)
           y_max = vals[1];
        if(vals[2] > z_max)
           z_max = vals[2]; 
        count++;
        findGain();
        findSpheredim();
      }
      
      //write file
      if(count == vecs.length) {
        writeData();
        print("output collected, written to " + filename);
      }
    }
  }
} 
