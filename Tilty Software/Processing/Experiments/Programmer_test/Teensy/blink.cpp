#line 1 "sketch_jun20a.ino"
#include <./libraries/Wire/Wire.h>

#include "Arduino.h"

void setup();
void loop();
#line 3
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(2500);
  digitalWrite(13, LOW);
  delay(2500);
}

