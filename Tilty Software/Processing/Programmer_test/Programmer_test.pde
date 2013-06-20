/*
This program compiles and downloads a program to the Teensy 3.0 automatically
*/

void setup() {
  //open("./Downloads/KSPManager.app");
  //open("/Applications/TextEdit.app");
  //open(sketchPath("") + "/KSPManager.app");
  println(sketchPath(""));
  String[] params = {"make", "-C", sketchPath("") + "Teensy/"};
  exec(params);
  delay(5000);
  String[] params2 = {"make", "-C", sketchPath("") + "Teensy/", "clean"};
  exec(params2);
}
