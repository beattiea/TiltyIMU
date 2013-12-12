import controlP5.Numberbox;
import javax.swing.ImageIcon;
import processing.serial.*;
import java.nio.ByteBuffer;

import controlP5.*;

float kP_value = 0.125;
float kI_value = 0.5;
float kD_value = 1.0;


void setup() {
  setupFrame();
  setupGUI();
  
}

void draw() {
  background(10);
  
  if (kP_box.isMousePressed()) {  kP_box.setText(str(kP_value));}
  if (kI_box.isMousePressed()) {  kI_box.setText(str(kI_value));}
  if (kD_box.isMousePressed()) {  kD_box.setText(str(kD_value));}
}




byte float_buffer[];

void floatToBytes(float value) {
  float_buffer = ByteBuffer.allocate(4).putFloat(value).array();
  for (int i = 0; i < 4; i++) {
    println(binary(float_buffer[i]));
  }
}

float bytesToFloat() {
  return ByteBuffer.wrap(float_buffer).getFloat();
}
