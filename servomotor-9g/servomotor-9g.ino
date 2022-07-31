void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // 0 angle
  goToAngle(500);
  //goToAngle(1000);
  //goToAngle(1250);
  //goToAngle(1500);
  // 90
  goToAngle(1500);
  //goToAngle(2000);
  //goToAngle(2250);
  // 180
  goToAngle(2500);
  goToAngle(1500);
  // goToAngle(2750);
}

void goToAngle(int time) {
  for (int i = 0; i <= 50; i++) 
  {
    digitalWrite(9, HIGH);
    delayMicroseconds(time);
    digitalWrite(9, LOW);
    delay(19);
  }
  delay(1000);
}
