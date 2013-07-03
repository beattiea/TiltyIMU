Serial myPort;

long connected = 0;
int timeout = 1000;

final char YAW = 'Y';
final char PITCH = 'P';
final char ROLL = 'R';
final char BATT = 'B';
final char ALT = 'A';
final char TEMP = 'T';


void serialSetup(int comm_port) {
  if (comm_port == -1) {  serialTest(); return;}
  try {
    myPort = new Serial(this, Serial.list()[comm_port], 115200);
    myPort.clear();
    myPort.bufferUntil('\n');
    println("Serial started on: " + Serial.list()[comm_port]);
  }
  catch (Exception serialException) {
    myPort = null;
    println("Not Connected to: " + Serial.list()[comm_port]);
  }
}


void serialEvent(Serial myPort) {
  String serial_data;
  
  while (myPort.available() != 0) {
    connected = millis();
    serial_data = myPort.readStringUntil('\n');
    
    switch (serial_data.charAt(0)) {
      case (ROLL): {  roll = float(serial_data.substring(1)); break;}
      case (PITCH): {  pitch = float(serial_data.substring(1)); break;}
      case (YAW): {  yaw = -float(serial_data.substring(1)); break;}
      case (BATT): {  batt_voltage = float(serial_data.substring(1)); break;}
      case (ALT): {  altitude = float(serial_data.substring(1)); break;}
      case (TEMP): {  temperature = float(serial_data.substring(1)); break;}
      default: {  println(serial_data); break;}
    }
  }
}


void checkConn() {
  if (millis() - connected > timeout) {
    connected = 0;
    serial_conn.setColorBackground(color(219,39,22))
               .setLabel("Select Serial Port")
               ;
  }
  else {
    serial_conn.setColorBackground(color(2,198,23))
               .setLabel("Connected")
               ;
  }
}

void serialTest() {
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
