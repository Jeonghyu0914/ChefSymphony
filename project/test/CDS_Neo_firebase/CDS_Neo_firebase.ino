#include <ESP32Firebase.h>
#include <WiFi.h>

const char *ssid = "KT_GiGA_7B86";
const char *password = "3add5bf491";

#define REFERENCE_URL "cookiot-test-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define NUMS 15

Adafruit_NeoPixel lin = Adafruit_NeoPixel(NUMS, LED_PIN, NEO_GRB+NEO_KHZ800);

#define NOISE_PIN 2

#define CDS_1 15
#define CDS_2 2

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

  lin.begin();
  lin.show();

  firebase.setInt("Status", 1);
  firebase.setInt("Nums", 1);
  Serial.println("Success");
}

void loop() {
  //밝기 측정
  // int sv1 = analogRead(CDS_1);
  // int sv2 = analogRead(CDS_2);
  // firebase.setInt("brightness_interior", sv1);
  // firebase.setInt("brightness_exterior", sv2);
  // Serial.print("bright1: ");
  // Serial.println(sv1);
  // Serial.print("bright2: ");
  // Serial.println(sv2);

  //소리 측정
  float sound = analogRead(NOISE_PIN);
  firebase.setFloat("noise", sound);
  Serial.println(sound);

  // int n = firebase.getInt("Nums");
  // for(int i = 0;i < n;i++){
  //   lin.setPixelColor(i, 0, 255, 0);
  // }
  // lin.show();
  delay(500);
}
