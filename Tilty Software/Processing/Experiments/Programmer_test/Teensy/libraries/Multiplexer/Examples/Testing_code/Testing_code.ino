#include <Multiplexer.h>

Multiplexer mux(19, 23);
int readMux[16];
int writeMux[16] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
int Delay = 1;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 16; i++) {
    mux.pinMode(i, DIGITAL_OUT);
  }
  
  mux.readAll(readMux);
}


int r = 0;
int g = 0;
int b = 0;
long start = 0;

void loop() {
  
  for (r = 0; g < 256; r++) {
    for (g = 0; b < 256; g++) {
      for (b = 0; r < 256; b++) {
        start = micros();
        while (micros() - start < 100) {
          mux.analogWrite(5, r);
          delayMicroseconds(125);
          mux.analogWrite(6, g);
          delayMicroseconds(125);
          mux.analogWrite(7, b);
          delayMicroseconds(125);
        }
      }
    }
  }
  /*
  mux.digitalWriteMux(7, HIGH);
  mux.digitalWriteMux(5, LOW);
  delay(1000);
  mux.digitalWriteMux(5, HIGH);
  mux.digitalWriteMux(6, LOW);
  delay(1000);
  mux.digitalWriteMux(6, HIGH);
  mux.digitalWriteMux(7, LOW);
  delay(1000);
  */
}
