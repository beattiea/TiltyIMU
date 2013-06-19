/*  Pings the Teensy to determine connection status  */
boolean pingTeensy() {
  char serial_return = ' ';
  long start_timer;
  long latency = 3000;
  
  //if (myPort == null) {  return false;}
  myPort.write(PING);
  
  //start_timer = millis();
  //myPort.clear();
  //while (serial_return != PING && millis() - start_timer < latency) {  serial_return = myPort.readChar();  print(serial_return); delay(1);}
  
  //if (serial_return == PING) {  return true;}
  //else {  myPort.clear(); return false;}
  return false;
}



void connected() {
  println("Connected!");
  serialStatus.setText("Connected!").setColorValue(color(0,255,0));
  readVar(VARIABLE_kP);
  readVar(VARIABLE_kI);
  readVar(VARIABLE_kD);
  readVar(VARIABLE_TRIM);
  readVar(VARIABLE_OFFSET);
  //readkP();
  //readkI();
  //readkD();
  //readTrimPots();
  //readAngleOffset();
}



/*  Reads the trim pot values on the TeensyWay  */
void setTrimVars(String data) {
  switch (data.charAt(1)) {
    case ('1'): {  trim_pots[0] = int(float(data.substring(2))); kP_slider.setValue(map(trim_pots[0], 0, 1023, 1, 200)); break;}
    case ('2'): {  trim_pots[1] = int(float(data.substring(2))); kI_slider.setValue(map(trim_pots[1], 0, 1023, 1, 200)); break;}
    case ('3'): {  trim_pots[2] = int(float(data.substring(2))); kD_slider.setValue(map(trim_pots[2], 0, 1023, 1, 200)); break;}
    case ('4'): {  trim_pots[3] = int(float(data.substring(2))); break;}
  }
}


/*  Automatically finds the possible TeensyWay serial ports and connects to the first one  */
//  NEEDS TO BE RE-WRITTEN FOR NEW SERIAL COMMUNICATION
void refresh() {
  String[] possibles = new String[Serial.list().length];
  int[] possibles_index = new int[Serial.list().length];
  int x = 0;
  
  //serialStatus.setText("Searching for TeensyWay serial port...")
  //            .setColorValue(color(255, 255, 0));
  
  if (myPort != null) {  myPort.stop();}

  for (int i = 0; i < Serial.list().length; i++) {
    if (!Serial.list()[i].substring(5, 7).toLowerCase().equals("cu")) {
      try {
        myPort = new Serial(this, Serial.list()[i], 115200);
        myPort.bufferUntil('\n');
        myPort.write(PING);
        delay(250);
        if (connected) {
          serialStatus.setText("Auto Connected!")// On: " + serialList.item(int(serialList.getValue())).getName())
                .setColorValue(color(0, 255, 0));
          readVar(VARIABLE_kP);
          readVar(VARIABLE_kI);
          readVar(VARIABLE_kD);
          return;
        }
        else {
          myPort.stop();
          println("Didn't connect to: " + Serial.list()[i]);
          serialList.removeItem(Serial.list()[i]);
        }
      }
      catch (Exception e) {
        //myPort.stop();
        serialList.removeItem(Serial.list()[i]);
        println(e.getMessage() + ": " + Serial.list()[i]);
      }
    }
  }
}



void readVar(char variable) {//                  ALL SERIAL FUNCTIONS SHOULD BE MADE TO RESEMBLE THIS
  myPort.write(str(READ) + str(variable));
}

void setVarFloat(char variable, float value) {
  myPort.write(str(SET) + str(variable) + str(value) + "0");
}

void saveVarFloat(char variable, float value) {
  myPort.write(str(SET) + str(variable) + str(value) + "0" + str(SAVE) + str(variable));
}

void loadVar(char variable) {
  myPort.write(str(LOAD) + str(variable));
}
