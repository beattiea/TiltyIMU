import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Programmer_test extends PApplet {

/*
This program compiles and downloads a program to the Teensy 3.0 automatically
*/

public void setup() {
  //open("./Downloads/KSPManager.app");
  //open("/Applications/TextEdit.app");
  //open(sketchPath("") + "/KSPManager.app");
  println(sketchPath(""));
  String[] params = {"make", "-C", sketchPath("") + "Teensy/"};
  exec(params);
  delay(5000);
  String[] params2 = {"make", "-C", sketchPath("") + "Teensy/", "clean"};
  exec(params2);
  
  exit();
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "Programmer_test" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
