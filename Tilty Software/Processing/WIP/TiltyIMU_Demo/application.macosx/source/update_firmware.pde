String file_path;
String file_name;

void setupFirmwareTest() {
  gui.addButton("update", 2)
     .setSize(120, 20)
     .setLabel("Update Firmware")
     .setPosition(int(2*scale), int(15*scale))
     ;
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
  chooseNewFirmware();
}

void uploadFirmware() {
  println("Path: " + file_path);
  println("Name: " + file_name);
  String[] command_line = {dataPath("") + "/tools/teensy_post_compile", "-file=" + file_name + "", "-path=" + file_path, "-tools=" + dataPath("tools")};
  for (int i = 0; i < 4; i++) {
    print(command_line[i] + " ");
  }
  exec(command_line);
  String[] command_line2 = {dataPath("") + "/tools/teensy_reboot", "-pmk20dx128", "-chalfkay"};
  exec(command_line2);
}
