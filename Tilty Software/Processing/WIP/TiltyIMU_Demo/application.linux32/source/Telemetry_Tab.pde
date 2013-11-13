Textlabel yaw_label, pitch_label, roll_label, batt_label, alt_label, temp_label;
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
                   .setSize(int(75*scale), int(100*scale))
                   .setBarHeight(int(6*scale))
                   .setScrollbarVisible(true)
                   .addItems(Serial.list())
                   .setLabel("Select Serial Port")
                   .setColorActive(0)
                   .setColorForeground(color(200,25,25))
                   ;
  serial_conn.captionLabel().style().marginTop = serial_conn.getBarHeight() / 2 - 6;
  serial_conn.addItem("Attempt to auto-connect", -1);
  serial_conn.addItem("Refresh list", -2);
                
  
  yaw_label = gui.addTextlabel("yawLabel")
                 .setText("Yaw: " + str(yaw))
                 .setPosition(width/2 - int(16*scale), int(150*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  pitch_label = gui.addTextlabel("pitchLabel")
                 .setText("Pitch: " + str(pitch))
                 .setPosition(width/2 - int(16*scale), int(155*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  roll_label = gui.addTextlabel("rollLabel")
                 .setText("Roll: " + str(roll))
                 .setPosition(width/2 - int(16*scale), int(160*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
  
  alt_label = gui.addTextlabel("altLabel")
                 .setText("Altitude: " + str(altitude))
                 .setPosition(width/2 - int(16*scale), int(165*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
                 
  temp_label = gui.addTextlabel("tempLabel")
                 .setText("Temperature: " + str(temperature))
                 .setPosition(width/2 - int(16*scale), int(170*scale))
                 .setColor(255)
                 .setFont(tabFont);
                 ;
  
  batt_label = gui.addTextlabel("battLabel")
                  .setText("Voltage: " + str(batt_voltage))
                  .setPosition(width - int(30*scale), int(2*scale))
                  .setColor(255)
                  .setFont(tabFont);
                  ;
                  
  gui.addButton("zero", 1)
     .setSize(93, 20)
     .setLabel("Zero Angles")
     .setPosition(width/2 - 46, int(178*scale))
     ;
}


void drawTelemetry() {
  if (gui.getTab("default").isActive()) {
    yaw_label.setText("Yaw: " + nfs(yaw, 3, 2) + "°");
    pitch_label.setText("Pitch: " + nfs(pitch, 2, 2) + "°");
    roll_label.setText("Roll: " + nfs(roll, 2, 2) + "°");
    batt_label.setText("Voltage:\n" + nfs(batt_voltage, 1, 2) + "v");
    if (!Float.isNaN(altitude)) {  alt_label.setText("Altitude: " + nfs(altitude, 3, 2) + " m");}
    else {  alt_label.setText("Altitude: Not detected");}
    if (!Float.isNaN(temperature)) {  temp_label.setText("Temperature: " + nfs(temperature, 2, 2) + "°C");}
    else {  temp_label.setText("Temperature: Not detected");}
    
    //  Battery voltage Meter 
    pushMatrix();
    stroke(255);
    fill(10);
    rect(width - 5*scale, 25*scale, 10, -24 * scale);
    noStroke();
    if (batt_voltage > min_batt) {  fill(0, 255, 0);}
    else {  fill(255, 0, 0);}
    rect(width - 5*scale, 25*scale, 10, constrain(-map(batt_voltage, 0, max_batt, 0, 24*scale), -24*scale, 0));
    popMatrix();
  }
}

void zero(int value) {
  if (myPort != null) {
    println("Zeroed!");
    myPort.write('Z');
    myPort.write('Y');
    myPort.write('P');
    myPort.write('Z');
    myPort.write('A');
  }
}
