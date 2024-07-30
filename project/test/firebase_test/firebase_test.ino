// #include <IOXhop_FirebaseESP32.h>
// #include <IOXhop_FirebaseStream.h>

#include <ESP32Firebase.h>
#include <WiFi.h>

const char *ssid = "KT_GiGA_7B86";
const char *password = "3add5bf491";

// #define FIREBASE_HOST "cookiot-test-default-rtdb.firebaseio.com/"
// #define FIREBASE_AUTH "5mTMqxKiPKvWoHuQfHJKwjD5KianKXKE8DMkpN0N"

#define REFERENCE_URL "cookiot-test-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  firebase.setInt("test_str/api", 2467);
  Serial.println("Success");
  // Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Firebase.setString("test1", "true");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    int a = Serial.read();
    firebase.setInt("another_test/new_test", a);
    Serial.println(a);
    Serial.println("...done...");
  }
  Serial.println(firebase.getInt("test_str/api"));
  delay(500);
}
