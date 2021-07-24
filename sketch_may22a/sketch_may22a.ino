int port = 10;
int max = 130;
int min = 0;
int count = 0;
int step = 2;
boolean isIncreasing = false;
void setup() {
  // put your setup code here, to run once:
    pinMode(port, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (count == max || count == min) {
    isIncreasing = !isIncreasing;
  }
  if (isIncreasing) {
    count = count + step;
  } else {
    count = count - step;
  }
  analogWrite(port, count);
  delay(25);
}
