#define MASTER
//#define SLAVE

#define slave1 "98D3,31,B0466B"
#define slave2 "98D3,31,B045DB"

void setup() {
    Serial1.begin(115200);
}

void loop() {
    connectToSlave(slave1);
}
