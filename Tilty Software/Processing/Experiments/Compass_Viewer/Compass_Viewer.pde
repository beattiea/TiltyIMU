import processing.serial.*;
Serial myPort;

float heading = 0;
float yaw = 0;

void setup() {
  size(displayWidth / 2, displayHeight / 2);
  background(0);
  
  smooth(8);
  
  noLoop();
  
  strokeWeight(10);
  
   println(Serial.list());
   
   myPort = new Serial(this, "/dev/tty.HC-05-DevB", 115200);
}

void draw() {
  background(0);
  translate(width / 2, height / 2);
  
  rotate(heading * PI / 180);
  stroke(0, 255, 0);
  line(0, 0, 0, -height);
  
  rotate(-heading * PI / 180);
  rotate(yaw * PI / 180);
  stroke(255, 0, 0);
  line(0, 0, 0, -height);
}

String serial_event = null;
int data_count = 0;

void serialEvent(Serial myPort) {
  serial_event = myPort.readStringUntil(10);
  if (serial_event != null) {
    //println(serial_event);
    if (serial_event.charAt(0) == 'H') {
      heading = float(serial_event.substring(1));
    }
    if (serial_event.charAt(0) == 'Y') {
      yaw = float(serial_event.substring(1));
    }
    float temp = heading - yaw;
    if (temp > 180) {
      temp -= 180;
    }
    if (temp < 0) {
      temp += 180;
    }
    
    println(temp);
    //println(data_count++);
    redraw();
  }
}
