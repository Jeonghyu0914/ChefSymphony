// 조도센서 2개 (in, out), 온습도 센서 1개, 소음측정센서 1개, LED strip 1개, 서보모터 2개

//library include
#include <WiFi.h>
#include <ESP32Firebase.h> //firebase module
#include <Adafruit_NeoPixel.h> //led strip module
#include <DHT11.h> //온습도 센서 module
#include <ESP32Servo.h> //서보 모터 module

//pin setting
//조도 센서
#define pin_CDS1 35
#define pin_CDS2 32
//온습도 센서
#define pin_dht 25
//소음측정 센서
#define pin_noise 33
//LED strip
#define pin_led 14
#define nums_led 30
//서보 모터
#define pin_sv1 12
#define pin_sv2 13

//WiFi setting
const char *ssid = "KT_GiGA_7B86"; //Wifi ssid here
const char *password = "3add5bf491"; //Wifi password here

//Firebase setting
#define REFERENCE_URL "cookiot-test-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

//LED setting
Adafruit_NeoPixel leds = Adafruit_NeoPixel(nums_led, pin_led, NEO_GRB+NEO_KHZ800);

//DHT setting
DHT11 TandH(pin_dht);

//Servo setting
Servo sv1;
Servo sv2;

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

  //LED
  leds.begin();
  leds.show();
  
  //servo
  sv1.attach(pin_sv1);
  sv2.attach(pin_sv2);

  //Wifi connect
  connect_wifi();

  //Firebase init
  firebase.setString("Status", "True");
  firebase.setInt("LED/NUMS", nums_led);
  firebase.setInt("LED/Brightness", 0);
  firebase.setInt("LED/R", 0);
  firebase.setInt("LED/G", 0);
  firebase.setInt("LED/B", 0);
  firebase.setInt("Brightness/interior", 0);
  firebase.setInt("Brightness/exterior", 0);
  firebase.setInt("Noise", 0);
  firebase.setInt("Temperature", 0);
  firebase.setInt("Humidity", 0);
  firebase.setInt("Servo/angle1", 0);
  firebase.setInt("Servo/angle2", 0);

  //init LED & Servo
  sv1.write(0);
  sv2.write(0);
  for(int i = 0;i < nums_led;i++){
    leds.setPixelColor(i, 0, 0, 0);
  }
  leds.show();

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

  //Getting Brightness And Upload to firebase
  int brightness_in = analogRead(pin_CDS1);
  int brightness_out = analogRead(pin_CDS2);
  firebase.setInt("Brightness/interior", brightness_in);
  firebase.setInt("Brightness/exterior", brightness_out);

  //Getting Noise And Upload to firebase
  int noise = analogRead(pin_noise);
  firebase.setInt("Noise", noise);

  //Turn on LED
  int numl = firebase.getInt("LED/NUMS");
  int brightl = firebase.getInt("LED/Brightness");
  int led_r = firebase.getInt("LED/R");
  int led_g = firebase.getInt("LED/G");
  int led_b = firebase.getInt("LED/B");
  leds.setBrightness(brightl);
  for(int i = 0;i < numl;i++){
    leds.setPixelColor(i, led_r, led_g, led_b);
  }
  leds.show();

  //Move Servo Motor
  int ang1 = firebase.getInt("Servo/angle1");
  int ang2 = firebase.getInt("Servo/angle2");
  sv1.write(ang1);
  sv1.write(ang2);

  //print all of them
  Serial.print("noise: ");
  Serial.println(noise);
  Serial.print("bright1: ");
  Serial.println(brightness_in);
  Serial.print("bright2: ");
  Serial.println(brightness_out);
  Serial.print("temperature: ");
  Serial.println(temperature);
  Serial.print("humidity: ");
  Serial.println(humidity);

  delay(50);

}
