/*
This program compiles and downloads a program to the Teensy 3.0 automatically
Currently can only run under a file path with no spaces
*/

void setup() {
  /*
  String[] params2 = {"make", "-C", sketchPath("Teensy/")};// + "Teensy/"};
  exec(params2);
  delay(5000);
  String[] params3 = {"make", "-C", sketchPath("") + "Teensy/", "clean"};
  exec(params3);
  delay(1000);
  */
  String os = System.getProperty("os.name");
  println(os);
  exit();
}
