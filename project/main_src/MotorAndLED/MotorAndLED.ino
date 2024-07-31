//LED strip 1개, 서보모터 2개, exterior 조도센서 1개

//library include
#include <WiFi.h>
#include <ESP32Firebase.h>  //firebase module
#include <Adafruit_NeoPixel.h> //led strip module
#include <ESP32Servo.h> //서보 모터 module

//pin setting
//조도 센서
#define pin_CDS 32
//LED strip
#define pin_led 12
#define num_led 30
//서보 모터
#define pin_sv1 25
#define pin_sv2 26

//WiFi setting
const char *ssid = "나우커피2G"; //Wifi ssid here
const char *password = "dee01dc173"; //Wifi password here

//Firebase setting
#define REFERENCE_URL "cookiot-test-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

//LED setting
Adafruit_NeoPixel leds = Adafruit_NeoPixel(num_led, pin_led, NEO_GRB+NEO_KHZ800);

//Servo setting
Servo sv1;
Servo sv2;

//wifi connecting function
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

void move_curtain(int bright) {
  // 밝기 값이 600보다 작으면 서보 모터 각도를 0도로, 크면 140도로 설정
  int angle = (bright < 600) ? 0 : 140;

  // 서보 모터를 해당 각도로 이동
  sv1.write(angle);
  sv2.write(angle);

  Serial.print("Brightness: ");
  Serial.print(bright);
  Serial.print(" -> Curtain angle: ");
  Serial.println(angle);
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

  //init LED & Servo
  sv1.write(0);
  sv2.write(0);
  for(int i = 0;i < num_led;i++){
    leds.setPixelColor(i, 0, 0, 0);
  }
  leds.show();

  //start
  Serial.println("-----Start!-----");
}

void loop() {
  //Getting Brightness And Upload to firebase
  int brightness_out = analogRead(pin_CDS);
  firebase.setInt("Brightness/exterior", brightness_out);

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
  sv2.write(ang2);

  //Moving curtain
  move_curtain(brightness_out);

  delay(500);
}
