void setup() {
  Serial.begin(115200);
}

void loop() {
  int sv1 = analogRead(32);
  //int sv2 = analogRead(12);
  Serial.print("Read1: ");
  Serial.println(sv1);
  //Serial.print("Read2: ");
  //Serial.println(sv2);
  delay(1000);
}
