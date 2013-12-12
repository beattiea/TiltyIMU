void sendScalars() {
  println("Send Scalars");
  updateFloat('p', float(kP_box.getText()));
  updateFloat('i', float(kI_box.getText()));
  updateFloat('d', float(kD_box.getText()));
}


void kPbox(String input) {
  println("kP Box:" + input);
  kP_value = float(input);
  updateFloat('p', float(input));
}

void kIbox(String input) {
  println("kI Box:" + input);
  kI_value = float(input);
  updateFloat('i', float(input));
}

void kDbox(String input) {
  println("kD Box:" + input);
  kD_value = float(input);
  updateFloat('d', float(input));
}
