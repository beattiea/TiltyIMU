import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class BoxAngleTesting extends PApplet {


Serial myPort;

boolean serial = false;

public void setup()  {
  size(displayWidth, displayHeight - 45, P3D);
  smooth(8);
  noStroke();
  fill(204);
  
  println(Serial.list());
  /*
  while (!serial) {
    try {  
      myPort = new Serial(this, "/dev/tty.usbmodem12341", 115200);
      myPort.bufferUntil(10);
    }
    catch (Exception e) {
      println(e.getMessage());
    }
  }
  myPort.write(1);
  */
}

float rot_x = 0;
float rot_y = 0;
float rot_z = 0;

public void draw()  {
  background(0);
  lights();

  translate(width/2, height/2, 0);
  rotateX(rot_x); 
  rotateY(rot_y); 
  rotateZ(rot_z);
  box(height / 5, height / 3, width / 20);
  
  if (!serial) {
    checkSerial();
  }
}

public void checkSerial() {
  for (int i = 0; i < Serial.list().length; i++) {
    if (Serial.list()[i].equals("/dev/tty.usbmodem12341")) {
      myPort = new Serial(this, "/dev/tty.usbmodem12341", 115200);
      myPort.bufferUntil(10);
      myPort.write(1);
      serial = true;
    }
  }
}

final char VARIABLE_PITCH = 'P';//  Read pitch PITCH
final char VARIABLE_ROLL = 'R';//  Read roll PITCH
final char VARIABLE_YAW = 'Y';//  Read yaw PITCH
String serial_event = null;
float yaw_offset = 0;
float pitch_offset = 0;//0.0993;
float roll_offset = 1.571f;//1.6233;

public void serialEvent(Serial myPort) {
  serial_event = myPort.readStringUntil(10);
  //print(serial_event);
  if (yaw_offset == 0 && serial_event.charAt(0) == VARIABLE_YAW) {
    yaw_offset = PApplet.parseFloat(serial_event.substring(1)) * PI/180;
  }
  if (pitch_offset == 0 && serial_event.charAt(0) == VARIABLE_PITCH) {
    //pitch_offset = (float(serial_event.substring(1)) + 0) * PI/180;
    //println("Pitch offset: " + str(pitch_offset));
  }
  if (roll_offset == 0 && serial_event.charAt(0) == VARIABLE_ROLL) {
    //roll_offset = (float(serial_event.substring(1)) + 90) * PI/180;
    println("Roll Offset: " + str(roll_offset));
  }
  switch (serial_event.charAt(0)) {
    case (VARIABLE_PITCH): {  rot_y = -PApplet.parseFloat(serial_event.substring(1)) * PI/180 - pitch_offset; break;}
    case (VARIABLE_ROLL): {  rot_x = PApplet.parseFloat(serial_event.substring(1)) * PI/180 - roll_offset; break;}
    //case (VARIABLE_YAW): {  rot_z = float(serial_event.substring(1)) * PI/180 - yaw_offset; break;}
    default: {  print(serial_event); break;}
  }
  //println("P: " + str(P) + "      I: " + str(I) + "      D: " + str(D) + "      PITCH: " + str(PITCH));
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "BoxAngleTesting" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
