Textarea serial_console;

void setupSerialConsole() {
  serial_console = gui.addTextarea("txt")
                  .setPosition(width / 2 - 250, height / 2)
                  .setSize(500,200)
                  .setFont(createFont("arial",12))
                  .setLineHeight(14)
                  .setColor(color(128))
                  .setColorBackground(color(255,100))
                  .setColorForeground(color(255,100));
                  ;
                  
  serial_console.moveTo("System");
}

int max_size = 2500;

void printConsole(String text) {
  
  print("New update: " + text);
  
  String newText = serial_console.getText();
  /*
  if (newText.length() + text.length() < max_size) {
    newText += text;
  }
  /*
  else {
    newText = newText.substring(text.length(), newText.length());
    newText += text;
  }
  */
  if (text != null && text != "\n") {
    serial_console.setText(text);
  }
}
