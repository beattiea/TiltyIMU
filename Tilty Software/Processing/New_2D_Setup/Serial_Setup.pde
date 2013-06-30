Serial myPort;

final char YAW = 'Y';
final char PITCH = 'P';
final char ROLL = 'R';

void serialSetup(int comm_port) {
  if (myPort != null) {  myPort.clear();  myPort.stop();}
  
  try {
    myPort = new Serial(this, Serial.list()[comm_port], 115200);
    myPort.clear();
    myPort.bufferUntil('\n');
    println("Serial started on: " + Serial.list()[comm_port]);
  }
  catch (Exception serialException) {
    myPort.stop();
    println(serialException.getMessage() + " on: " + Serial.list()[comm_port]);
  }
}

void serialEvent(Serial myPort) {
  String serial_data;
  
  while (myPort.available() != 0) {
    serial_data = myPort.readStringUntil('\n');
    println(serial_data);
    
    switch (serial_data.charAt(0)) {
      case (PITCH): {  roll = float(serial_data.substring(1)); break;}
      case (ROLL): {  pitch = float(serial_data.substring(1)); break;}
      case (YAW): {  yaw = -float(serial_data.substring(1)); break;}
      default: {  println(serial_data); break;}
    }
  }
}
