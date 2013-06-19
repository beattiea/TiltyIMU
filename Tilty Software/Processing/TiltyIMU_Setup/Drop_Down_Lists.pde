DropdownList serialList;

void setupDropDowns() {
  setupSerialList(20, 25);
}

void setupSerialList(int x, int y) {//  List needs name to be changed to value selected and enlarged
  int index = 0;
  serialList = cp5.addDropdownList("serialList")
                  .setPosition(x, y)
                  .setItemHeight(20)
                  .setBarHeight(20)
                  .setSize(150, 200)
                  .setLabel("Available Serial Ports")
                  ;
  serialList.getCaptionLabel().setFont(createFont("arial", 8));
          
  for (int i = 0; i < Serial.list().length; i++) {
    if (!Serial.list()[i].substring(5, 7).toLowerCase().equals("cu")) {
      serialList.addItem(Serial.list()[i], index);
      index ++;
    }
  }
}

void serialList(String value) {
  println(value);
}
