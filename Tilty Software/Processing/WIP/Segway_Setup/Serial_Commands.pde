void updateFloat(char command, float value) {
  if (myPort != null) {
    myPort.write(command);
    floatToBytes(value);
    for (int i = 0; i < 4; i++) {
      myPort.write(float_buffer[i]);
    }
  }
}
