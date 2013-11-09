void setup() {
    delay(100);
    Serial.begin(115200);
    Serial1.begin(115200);
  
    pinMode(15, OUTPUT);
    digitalWrite(15, LOW);
}

long start;

void loop() {
    if (Serial.available()) {
        while (Serial.available()) {
            char data = Serial.read();
            
            if (data == '`') {
                digitalWrite(15, !digitalRead(15));
                Serial.println(digitalRead(15) ? "Command pin set HIGH" : "Command pin set LOW");
                Serial1.print("\r\n");
                break;
            }
            
            else {
                Serial1.print(data);
                start = micros();
            }
        }
        Serial1.print("\r\n");
        Serial.flush();
    }
    
    if (Serial1.available()) {
       char data = Serial1.read();
       if (data == '\n') {
           Serial.print(data);
           //Serial.print(micros() - start);
           //Serial.println(" microseconds to respond");
       }
       
       else {
           Serial.print(data);
       }
    }
}
