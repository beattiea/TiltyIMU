ControlP5 gui;

PFont font = createFont("Arial", 18, true);
PFont globalFont = createFont("Arial", 12, true);
ControlFont tabFont = new ControlFont(font, 18);
ControlFont global = new ControlFont(globalFont, 12);
    
DropdownList serial_conn;
Button send_scalars;
Textfield kP_box, kI_box, kD_box;

void setupGUI() {
  gui = new ControlP5(this);
  gui.setControlFont(global);
  
  setupSerialList();
  setupPIDscalars(275, 2);
  setupToolTips();
}


void setupSerialList() {
  serial_conn = gui.addDropdownList("serial")
                   .setPosition(10, 22)
                   .setSize(250, 200)
                   .setBarHeight(20)
                   .setScrollbarVisible(true)
                   .addItems(Serial.list())
                   .setLabel("Select Serial Port")
                   .setColorActive(0)
                   .setColorForeground(color(200,25,25))
                   ;
  serial_conn.captionLabel().style().marginTop = serial_conn.getBarHeight() / 2 - 8;
  serial_conn.addItem("Attempt to auto-connect", -1);
  serial_conn.addItem("Refresh list", -2);
}


void setupPIDscalars(int x_pos, int y_pos) {
  send_scalars = gui.addButton("sendScalars")
                    .setPosition(x_pos + 150, y_pos)
                    .setSize(120, 135) // allows for 40 point tall boxes and 5 point spacing
                    .setLabel("Update Scalars")
                    .setColorActive(color(255, 0, 0))
                    .registerTooltip("Send the power scaling values to the Tilty")
                    ;
                    
  kP_box = gui.addTextfield("kPbox")
              .setPosition(x_pos, y_pos)
              .setSize(145, 18)
              .setText("Not yet set")
              .setLabel("Proportional Power")
              .registerTooltip("Changes the proportional power applied based on tilt angle")
              ;
  kI_box = gui.addTextfield("kIbox")
              .setPosition(x_pos, y_pos + 50)
              .setSize(145, 18)
              .setText("Not yet set")
              .setLabel("Integral Power")
              .registerTooltip("Changes the accumulating power applied based on tilt angle")
              ;
  kD_box = gui.addTextfield("kDbox")
              .setPosition(x_pos, y_pos + 100)
              .setSize(145, 18)
              .setText("Not yet set")
              .setLabel("Derivative Power")
              .registerTooltip("Changes the power applied based on rate and direction of tilt")
              ;
                    
}


void setupToolTips() {
  gui.getTooltip().setDelay(500);
  
}


void controlEvent(ControlEvent event) {
  if (event.isGroup()) {
    if (event.getGroup().toString().equals("serial [DropdownList]")) {  serialSetup(int(event.getValue()));}
  }
  
  else if (event.isController()) {
    println("event from controller : "+event.getController().getValue()+" from "+event.getController());
  }
}
