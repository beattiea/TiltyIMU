String file_path;
String file_name;

void setupFirmwareTest() {
  gui.addButton("update", 2)
     .setSize(120, 20)
     .setLabel("Update Firmware")
     .setPosition(width / 2 - 60, int(120*scale))
     ;
     
     gui.getController("update").moveTo("System");
}

void chooseNewFirmware() {
  selectInput("Select a new .hex file", "fileSelected");
}

void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    file_path = selection.getAbsolutePath();
    //file_name = file_path.substring(0, file_path.length() - 4);
    file_name = selection.getName().substring(0, selection.getName().length() - 4);
    file_path = selection.getParent();
    uploadFirmware();
  }
}

void update() {
  //chooseNewFirmware();
  forceUpdate();
}

void uploadFirmware() {
  println("Path: " + file_path);
  println("Name: " + file_name);
  
  if (System.getProperty("os.name").equals("Mac OS X")) {
    String[] command_line = {dataPath("") + "/tools/Mac/teensy_post_compile", "-file=" + file_name + "", "-path=" + file_path, "-tools=" + dataPath("tools/Mac")};
    //for (int i = 0; i < 4; i++) {  print(command_line[i] + " ");}
    exec(command_line);
    
    delay(3000);
    println("Rebooting...");
    
    String[] command_line2 = {dataPath("tools/Mac") + "/teensy_reboot", ""};// "-pmk20dx128", "-chalfkay"};
    exec(command_line2);
  }
  
  if (System.getProperty("os.name").substring(0, 7).equals("Windows")) {
    String[] command_line = {dataPath("") + "/tools/Windows/teensy_post_compile.exe", "-file=" + file_name + "", "-path=" + file_path, "-tools=" + dataPath("tools/Windows")};
    exec(command_line);
    String[] command_line2 = {dataPath("") + "/tools/Windows/teensy_reboot.exe", ""};//, "-pmk20dx128", "-chalfkay"};
    exec(command_line2);
  }
  else {
    println(System.getProperty("os.name"));
  }
}

void forceUpdate() {
  file_name = "TiltyTest.cpp";
  file_path = dataPath("");
  uploadFirmware();
}
