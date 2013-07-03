int bauds[] = {9600, 14400, 19200, 28800, 38400, 57600, 115200};

void setup() {
  Serial.begin(115200);
  pinMode(15, OUTPUT);
  while (!Serial) {}
  
  digitalWrite(15, HIGH);
  
  Serial.println("Beginning test...");
  findBaud();
}

void loop() {
  if (Serial.available()) {
    delay(1);
    while(Serial.available()) {
      char data = Serial.read();
      Serial.print(data);
      Serial1.write(data);
    }
    Serial1.write("\r\n");
    Serial.println();
  }
  
  if (Serial1.available()) {
    while(Serial1.available()) {
      Serial.print(char(Serial1.read()));
    }
  }
}

void findBaud() {
  boolean cmd = false;

  for (int i = 0; i < sizeof(bauds); i++) {
    
    Serial1.begin(bauds[i]);
    //Serial1.write("AT+ROLE=1\r\n");
    //delay(1000);
    Serial1.write("AT+ROLE=0\r\n");
    //delay(25);
    
    int start = millis();
    while (millis() - start < 10000) {
      if (Serial1.available()) {
        Serial.print("Received: ");
        while (Serial1.available()) {
          Serial.print(char(Serial1.read()));
          delay(1);
        }
      }
    }
    
  }
}
