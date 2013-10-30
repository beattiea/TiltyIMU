void setup() {
    Serial.begin(115200);
  Serial1.begin(115200);
  
  pinMode(15, OUTPUT);
}

long start;

void loop() {
    if (Serial.available()) {
        char data = Serial.read();
      
        if (data == '`') {
            digitalWrite(15, !digitalRead(15));
        }
        
        else {
            Serial1.print(data);
            start = micros();
        }
    }
    
    if (Serial1.available()) {
       char data = Serial1.read();
       if (data == '\n') {
           Serial.print(data);
           //Serial.print(micros() - start);
           //Serial.println(" microseconds to response");
       }
       
       else {
           Serial.print(data);
       }
    }
}
