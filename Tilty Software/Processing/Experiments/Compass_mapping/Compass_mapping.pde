import processing.serial.*;
Serial myPort;

float heading = 0;
float yaw = 0;

float x = 0;
float y = 0;
float z = 0;

void setup() {
  size(displayWidth - 50, displayHeight - 50);
  background(0);
  
  noLoop();
  
  strokeWeight(10);
  stroke(255);
  
   println(Serial.list());
   
   myPort = new Serial(this, "/dev/tty.usbmodem12341", 115200);
   
   translate(width / 2, height / 2);
   line(-width, 0, width, 0);
   line(0, -height, 0, height);
   
   strokeWeight(3);
}

void draw() {
  //println(frameRate);
  /*
  //background(0);
  translate(width / 2, height / 2);
  
  rotate(heading * PI / 180);
  stroke(0, 255, 0);
  line(0, 0, 0, -height);
  
  rotate(-heading * PI / 180);
  rotate(yaw * PI / 180);
  stroke(255, 0, 0);
  line(0, 0, 0, -height);
  */
}

void draw_xy() {
  translate(width / 2, height / 2);
  stroke(255, 0, 0);
  line(x, y, x+1, y+1);
  translate(-width / 2, -height / 2);
  //redraw();
}

void draw_xz() {
  translate((width / 4) * 3, (height / 4));
  stroke(0, 255, 0);
  line(x, z, x, z);
  translate(-(width / 4) * 3, -(height / 4));
  //redraw();
}

void draw_yz() {
  translate((width / 4), (height / 4) * 3);
  stroke(0, 0, 255);
  line(y, z, y, z);
  translate(-(width / 4), -(height / 4) * 3);
  //redraw();
}

String serial_event = null;
int data_count = 0;

int divider = 3;

void serialEvent(Serial myPort) {
  serial_event = myPort.readStringUntil(10);
  if (serial_event != null) {
    
    char data = serial_event.charAt(0);
    print(serial_event);
    if (serial_event.charAt(0) == 'C') {
      heading = float(serial_event.substring(1));
    }
    if (serial_event.charAt(0) == 'I') {
      yaw = float(serial_event.substring(1));
    }
    
    if (data == 'X') {
      x = float(serial_event.substring(1)) / divider;
      //println("X: " + x);
      //draw_xy();
      //draw_xz();
    }
    if (data == 'Y') {
      y = float(serial_event.substring(1)) / divider;
      //println("Y: " + y);
      draw_xy();
      //draw_yz();
    }
    if (data == 'Z') {
      z = float(serial_event.substring(1)) / divider;
      //println("Z: " + z);
      //draw_xz();
      //draw_yz();
    }
    
    float temp = heading - yaw;
    if (temp > 180) {
      temp -= 180;
    }
    if (temp < 0) {
      temp += 180;
    }
    
    //println(temp);
    //println(data_count++);
    redraw();
  }
}
