import processing.serial.*;

Serial bt;
char d[] = {5, 15, 27, 53, 71, 163, 127, 221};
char d_temp[];

void setup() {
  bt = new Serial(this, "/dev/cu.usbmodem12341", 460800);
  
  delay(100);
  
  for (int i = 0; i < 128; i++) {
    bt.write(i);
    bt.write(d[i % 8]);
    delay(5);
  }
}

int fails = 0;
int rec = 0;

void serialEvent(Serial bt) {
  while (bt.available() > 1) {
    char data = bt.readChar();
    print(data);
    /*
    if (data != 1 && data != 3 && data != 7 && data != 15 && data != 31 && data != 63 && data != 63 && data != 127 && data != 255) {
      print(data);
    }
    */
    /*
    if (d[int(data) % 8] != bt.readChar() && rec <= 256) {
      println(int(data) + " Failed!");
      rec += 2;
    }
    else {
      print(data);
    }
    */
  }
}

void draw() {
  background(0);
}
