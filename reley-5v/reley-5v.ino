void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  
}

void loop() {
  digitalWrite(7, LOW);
  delay(5000);
  digitalWrite(7, HIGH);
  delay(5000);

}
