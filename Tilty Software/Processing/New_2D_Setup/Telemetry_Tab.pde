Textlabel yaw_label, pitch_label, roll_label;
DropdownList serial_conn;

void setupTelemetryTab() {
  color background = color(100, 100, 100);
  color Label = color(255);
  color active = color(127, 127, 127);
  
  
  gui.getTab("default")
     .setLabel("Main")
     .setColorBackground(background)
     .setColorLabel(Label)
     .setColorActive(active)
     .getCaptionLabel().setFont(tabFont)
     ;
     
  serial_conn = gui.addDropdownList("serial")
                   .setPosition(int(2*scale), int(13*scale))
                   .setSize(int(75*scale), int(50*scale))
                   .setBarHeight(int(6*scale))
                   .setScrollbarVisible(true)
                   .addItems(Serial.list())
                   .setLabel("Serial Ports")
                   ;
                
  
  yaw_label = gui.addTextlabel("yawLabel")
                 .setText("Yaw: " + str(t))
                 .setPosition(width/2 - int(20*scale), int(150*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  pitch_label = gui.addTextlabel("pitchLabel")
                 .setText("Pitch: " + str(t))
                 .setPosition(width/2 - int(20*scale), int(155*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  roll_label = gui.addTextlabel("rollLabel")
                 .setText("Roll: " + str(t))
                 .setPosition(width/2 - int(20*scale), int(160*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
}


void drawTelemetry() {
  if (gui.getTab("default").isActive()) {
    yaw_label.setText("Yaw: " + str(yaw));
    pitch_label.setText("Pitch: " + str(pitch));
    roll_label.setText("Roll: " + str(roll));
  }
}
