#define sound 35
void setup() {
  Serial.begin(115200);
}

void loop() {
  float val = analogRead(sound);
  Serial.println(val);
  delay(500);
}
