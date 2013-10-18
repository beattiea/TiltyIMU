/*
Indicator library
turn on
Turn off
Toggle (on time, off time, cycles)
*/


unsigned long buzzer_previous = 0;
int buzzer_state = LOW;

void buzzerPulse(int interval) {
  if (millis() - buzzer_previous > interval) {
    buzzer_previous = millis();
    
    buzzer_state = !buzzer_state;
    digitalWriteFast(BUZZER, buzzer_state);
  }
}

void buzzerOff() {
  if (buzzer_state == HIGH) {
    buzzer_state = LOW;
    digitalWriteFast(BUZZER, buzzer_state);
  }
}

void buzzerOn() {
  if (buzzer_state == LOW) {
    buzzer_state = HIGH;
    digitalWriteFast(BUZZER, buzzer_state);
  }
}
