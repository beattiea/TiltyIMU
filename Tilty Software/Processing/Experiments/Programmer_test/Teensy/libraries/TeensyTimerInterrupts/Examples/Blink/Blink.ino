#include <TeensyTimerInterrupts.h>

//  This example demonstrates the timer interrupt capability on the Teensy 3.0
//  There are 3 interrupt timers (0, 1, 2)
//  Any variables modified by interrupt timer routines should be marked volatile

void setup(){
  pinMode(13, OUTPUT);
  attachTimerInterrupt(0, blink, 500);//  Attach an interrupt timer to run blink() every 500ms
}
 
void loop(){
  delay(2000);
  if (millis() > 5000 && millis() < 7000) {
    detachTimerInterrupt(0);//  Disables interrupt timer 0 after 5 seconds
    digitalWrite(13, LOW);
  }
  else if (millis() >= 7000 && millis() < 15000) {
    attachTimerInterrupt(1, blink, 200);//  Attach an interrupt timer to run blink() every 200ms
  }
  else if (millis() >= 15000) {
    detachTimerInterrupts();//  Disables all interrupt timers after 15 seconds
  }
}

void blink() {
  digitalWrite(13, !digitalRead(13));
}