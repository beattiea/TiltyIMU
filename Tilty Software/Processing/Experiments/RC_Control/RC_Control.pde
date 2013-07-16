import processing.serial.*;

Serial myPort;

void setup() {
  size(255, 255);
  
  myPort = new Serial(this, "/dev/cu.usbmodem12341", 115200);
  
  delay(100);
  
}

int fails = 0;
int rec = 0;

void serialEvent(Serial myPort) {
  while (myPort.available() > 1) {
    char data = myPort.readChar();
    print(data);
  }
}

int xPos = 0;
int yPos = 0;

void draw() {
  background(0);
  translate(127, 127);
  if (mousePressed && mouseX != xPos) {
    xPos = mouseX;
    myPort.write('S');
    myPort.write(xPos);
  }
  if (mousePressed && mouseY != yPos) {
    yPos = mouseY;
    myPort.write('F');
    myPort.write(yPos);
  }
    //print("X: " + (mouseX - 127) + "\tY: " + (127 - mouseY));
  if (!mousePressed && (xPos != 127 || yPos != 127)) {
    xPos = 127;
    yPos = 127;
    myPort.write('F');
    myPort.write(127);
    myPort.write('S');
    myPort.write(127);
  }
  
  delay(5);
}
