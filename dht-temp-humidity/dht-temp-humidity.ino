int port = 4;
int waitNumber = 10000;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  int res = readTHdata();
  if (res == -1) Serial.println("Error");
  else Serial.println(res);
  //Serial.print("Error");
  delay(2000);
}

int readTHdata() {
    int bits[40];
    unsigned long timeStart;
    pinMode(port, OUTPUT);
    // ask session
    digitalWrite(port, LOW);
    delay(18);
    digitalWrite(port, HIGH);
    delayMicroseconds(40);
    pinMode(port, INPUT);
    // wait for response
    int res = waitUntil(port, LOW, waitNumber);
    if (res == -1) return -1;
    res = waitUntil(port, HIGH, waitNumber);
    if (res == -1) return -1;
    // data transfer starts
    for (int i = 0; i < 40; i++) {
        res = waitUntil(port, LOW, waitNumber);
        if (res == -1) return -1;
        res = waitUntil(port, HIGH, waitNumber);
        if (res == -1) return -1;
        timeStart = micros();
        res = waitUntil(port, LOW, waitNumber);
        if (res == -1) return -1;
        if (micros() - timeStart >= 40) bits[i] = 1;
        else bits[i] = 0;
    }
    return toDecimal(bits, 16, 23);
}

int toDecimal(int arr[], int posStart, int posEnd) {
    int acc = arr[posStart];
    int i = posStart + 1;
    while(i <= posEnd) {
        acc <<= 1;
        acc += arr[i];
        i++;
    }
    return acc;
}

int waitUntil(int port, int waitValue, int iterNumber) {
    while(digitalRead(port) != waitValue) {
        if (iterNumber == 0) return -1;
        iterNumber--;  
    }
    return 0;
}
