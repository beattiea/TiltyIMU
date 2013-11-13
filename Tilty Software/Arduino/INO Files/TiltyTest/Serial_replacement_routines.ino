//            Print            //
void print(char* data) {
    if (Serial) {
        Serial.print(data);
    }
    else {
        Serial1.print(data);
    }
}

void print(char data) {
    if (Serial) {
        Serial.print(data);
    }
    else {
        Serial1.print(data);
    }
}

void print(float data) {
    if (Serial) {
        Serial.print(data);
    }
    else {
        Serial1.print(data);
    }
}

void print(int data) {
    if (Serial) {
        Serial.print(data);
    }
    else {
        Serial1.print(data);
    }
}



//            Print New Line            //
void println() {
    if (Serial) {
        Serial.println();
    }
    else {
        Serial1.println();
    }
}

void println(char* data) {
    if (Serial) {
        Serial.println(data);
    }
    else {
        Serial1.println(data);
    }
}

void println(char data) {
    if (Serial) {
        Serial.println(data);
    }
    else {
        Serial1.println(data);
    }
}

void println(float data) {
    if (Serial) {
        Serial.println(data);
    }
    else {
        Serial1.println(data);
    }
}

void println(int data) {
    if (Serial) {
        Serial.println(data);
    }
    else {
        Serial1.println(data);
    }
}




//            Available            //
int available() {
    if (Serial) {    return Serial.available();}
    else {    return Serial1.available();}
}



//            Read            //
char read() {
    if (Serial) {    return Serial.read();}
    else {    return Serial1.read();}
}
