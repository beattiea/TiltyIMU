import processing.serial.*;
Serial myPort;

boolean serial = false;

void setup()  {
  size(5, 5);
  smooth(8);
  noStroke();
  fill(204);
  
  println(Serial.list());

  myPort = new Serial(this, "/dev/tty.usbmodem12341", 115200);
}

void draw() {
  
}

void serialEvent(Serial myPort) {
  print(char(myPort.read()));
}
