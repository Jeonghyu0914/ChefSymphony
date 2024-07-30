//버튼들로 주문 키오스크 구현

//library include
#include <WiFi.h>
#include <ESP32Firebase.h> //firebase module

//pin setting
#define pin_btn1 32
#define pin_btn2 33
#define pin_btn3 34
#define pin_btn4 35
#define pin_btn5 36
#define pin_btn6 39

//WiFi setting
const char *ssid = "KT_GiGA_7B86"; //Wifi ssid here
const char *password = "3add5bf491"; //Wifi password here

//Firebase setting
#define REFERENCE_URL "cookiot-test-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

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

  //Switch 정의
  //PULL UP 방식 사용
  pinMode(pin_btn1, INPUT_PULLUP);
  pinMode(pin_btn2, INPUT_PULLUP);
  pinMode(pin_btn3, INPUT_PULLUP);
  pinMode(pin_btn4, INPUT_PULLUP);
  pinMode(pin_btn5, INPUT_PULLUP);
  pinMode(pin_btn6, INPUT_PULLUP);

  Serial.println("-----Start-----")
}

void loop() {
  int activate1 = digitalRead(pin_btn1);
  int activate2 = digitalRead(pin_btn2);
  int activate3 = digitalRead(pin_btn3);
  int activate4 = digitalRead(pin_btn4);
  int activate5 = digitalRead(pin_btn5);
  int activate6 = digitalRead(pin_btn6);

  if(activate1 == LOW){
    firebase.setInt("Order/1", 1);
  }
  if(activate2 == LOW){
    firebase.setInt("Order/2", 1);
  }
  if(activate3 == LOW){
    firebase.setInt("Order/3", 1);
  }
  if(activate4 == LOW){
    firebase.setInt("Order/4", 1);
  }
  if(activate5 == LOW){
    firebase.setInt("Order/5", 1);
  }
  if(activate6 == LOW){
    firebase.setInt("Order/6", 1);
  }

  delay(500);
}
