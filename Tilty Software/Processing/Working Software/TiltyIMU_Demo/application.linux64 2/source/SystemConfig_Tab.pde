

void setupSystemTab() {
  color background = color(90, 90, 90);
  color label = color(255);
  color active = color(137, 137, 137);
  
  gui.addTab("System")
     .setLabel("Tilty Configuration")
     .setColorBackground(background)
     .setColorLabel(label)
     .setColorActive(active)
     .getCaptionLabel().setFont(tabFont)
     ;
     
}

void drawSystem() {
  
}
