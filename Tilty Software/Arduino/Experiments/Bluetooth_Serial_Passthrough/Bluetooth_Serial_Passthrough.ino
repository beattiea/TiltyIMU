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
            
            else if (data == '~') {
                Serial1.print("AT+LINK:98D3,31,B0466B\r\n");
                Serial1.flush();
                delay(5000);
                digitalWrite(15, LOW);
                for (int i = 0; i < 30; i++) {
                    Serial.print(".");
                    delay(1000);
                }
                Serial.println();
                digitalWrite(15, HIGH);
                Serial1.print("AT+DISC\r\n");
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
