typedef void (*voidFunction_t)(void *);
typedef void (*byteFunction_t)(char *);

voidFunction_t fp[2] = {Page2, Page3};

int Page2(char * y) {
  Serial.print("2: ");
  Serial.println(y);
}

int Page3(char * x) {
  Serial.print("3: ");
  Serial.println(x);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  char v[4] = {'1','2'};
  char u[4] = {'3', '4'};

  fp[0](v);
  fp[1](u);
}
