//조도센서 1개(in), 온습도 센서 1개, 소음측정센서 2개

//library include
#include <WiFi.h>
#include <ESP32Firebase.h> //firebase module
#include <DHT11.h> //온습도 센서 module

//pin setting
//조도 센서
#define pin_CDS 32
//온습도 센서
#define pin_dht 25
//소음측정 센서
#define pin_noise 33
#define pi_noise2 35

//WiFi setting
const char *ssid = "KT_GiGA_7B86"; //Wifi ssid here
const char *password = "3add5bf491"; //Wifi password here

//Firebase setting
#define REFERENCE_URL "cookiot-test-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

//DHT setting
DHT11 TandH(pin_dht);

//wifi connect function
void connect_wifi(){
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
}

void setup() {
  Serial.begin(115200);

  //Wifi connect
  connect_wifi();

  //Firebase init
  // firebase.setString("Status", "True");
  // firebase.setInt("LED/NUMS", nums_led);
  // firebase.setInt("LED/Brightness", 0);
  // firebase.setInt("LED/R", 0);
  // firebase.setInt("LED/G", 0);
  // firebase.setInt("LED/B", 0);
  // firebase.setInt("Brightness/interior", 0);
  // firebase.setInt("Brightness/exterior", 0);
  // firebase.setInt("Noise", 0);
  // firebase.setInt("Temperature", 0);
  // firebase.setInt("Humidity", 0);
  // firebase.setInt("Servo/angle1", 0);
  // firebase.setInt("Servo/angle2", 0);

  //start
  Serial.println("-----Start!-----");
}

void loop() {
  //Getting Temperature & Humidity And Upload to firebase
  int temperature, humidity;
  int result = TandH.readTemperatureHumidity(temperature, humidity);
  //예외처리
  if(result != 0){
    Serial.println(DHT11::getErrorString(result));
  }
  firebase.setInt("Temperature", temperature);
  firebase.setInt("Humidity", humidity);

  //Getting Inner Brightness And Upload to firebase
  int brightness_in = analogRead(pin_CDS);
  firebase.setInt("Brightness/interior", brightness_in);
  Serial.print("CDS: ");
  Serial.println(brightness_in);

  //Getting Noise And Upload to firebase
  int noise = analogRead(pin_noise);
  firebase.setInt("Noise", noise);
  Serial.print("Noise: ");
  Serial.println(noise);

  delay(100);
}
