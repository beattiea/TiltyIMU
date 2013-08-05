void setup() {
  Serial.begin(115200);
}

int data;

void loop() {
  long start = micros();

  for (int i = 0; i < 1024; i++) {
    for (int x = 0; x < 8; x++) {
      data = digitalRead(x);
    }
  }
  long stop = micros();

  Serial.print("Average time to read all 8 pins using digitalRead() (us): ");
  Serial.println((stop - start) / 1024.0);
  Serial.print("Average time to read a pin (us): ");
  Serial.println((stop - start) / 8192.0);
  Serial.println("=====================================\n");
  
  start = micros();

  for (int i = 0; i < 1024; i++) {
    for (int x = 0; x < 8; x++) {
      data = PINB;
    }
  }
  stop = micros();

  Serial.print("Average time to read all 8 pins using pin data register (us): ");
  Serial.println((stop - start) / 1024.0);
  Serial.print("Average time to read a pin (us): ");
  Serial.println((stop - start) / 8192.0);
  Serial.println("=====================================\n");
  
  start = micros();

  for (int i = 0; i < 1024; i++) {
    for (int x = 0; x < 8; x++) {
      data = PINB | 0b00100000;
    }
  }
  stop = micros();

  Serial.print("Average time to read all 8 pins masked to 1 pin (us): ");
  Serial.println((stop - start) / 1024.0);
  Serial.print("Average time to read a pin using bitmask (us): ");
  Serial.println((stop - start) / 8192.0);
  Serial.println("=====================================\n");
}

