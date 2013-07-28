int bauds[] = {9600, 14400, 19200, 28800, 38400, 57600, 115200};

void setup() {
  Serial.begin(115200);
  Serial1.begin(230400);
  
  pinMode(15, OUTPUT);
  
  while (!Serial) {}
  
  digitalWrite(15, HIGH);
  
  //Serial.println("Beginning test...");
  //findBaud();
  
  delay(100);
  Serial1.write("AT+UART=460800,0,0\r\n");
  delay(20);
  digitalWrite(15, LOW);
  delay(100);
  if (Serial1.available()) {
    while (Serial1.available()) {
      Serial.print(char(Serial1.read()));
    }
  }
  else {  Serial.println("test failed");
  delay(25);
  
  digitalWrite(15, LOW);
  Serial1.end();
  delay(50);
  Serial1.begin(460800);
  } 
}

void loop() {
  long start = micros();
  Serial1.println("Hello World!");
  long stop = micros();
  Serial.print("Time to send 13 bytes: ");
  Serial.println(stop - start);
  
  if (Serial1.available()) {
    while (Serial1.available()) {
      Serial.print(char(Serial1.read()));
    }
    Serial.println();
  }
  delay(200);
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
