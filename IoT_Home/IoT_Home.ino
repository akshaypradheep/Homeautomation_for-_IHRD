#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <FirebaseArduino.h>
#define FIREBASE_HOST "myextprojects.firebaseio.com"
#define FIREBASE_AUTH "953cVa49ZEJVG4oq400eCQrgeLk9NDJZR83S5TbI"
#define WIFI_SSID "SMART_HOME"
#define WIFI_PASSWORD "nodemcu8266"

const int fan = D0;
const int light = D1;
const int pp = D3;
const int  pir = D4;
const int buz = D7;
const int motor = D2;

void setup() {
  dht.begin();
  pinMode(fan,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(pp,OUTPUT);
  pinMode(pir,INPUT);
  

  
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop() {
  float t = dht.readTemperature();
  float f = dht.readHumidity();
  Firebase.setInt("t",t);
  Firebase.setInt("f",f);
  
 /* Firebase.setFloat("number", 42.0);
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }*/
 String  _fan = Firebase.getString("FAN");
 String  _light = Firebase.getString("LIGHT");
 String  _motor = Firebase.getString("MOTOR");
 String _pp = Firebase.getString("PLUG");
 if(_fan == "1"){
  digitalWrite(fan,LOW);
 }
 if(_fan == "0"){
  digitalWrite(fan,HIGH);
 }
 if(_light == "1"){
   digitalWrite(light,LOW);
 }
 if(_light == "0"){
   digitalWrite(light,HIGH); 
 }
 if(_motor =="1"){
  digitalWrite(motor,LOW);
 }
  if(_motor =="0"){
  digitalWrite(motor,HIGH);
  }
  if(_pp=="0"){
    digitalWrite(pp,HIGH);
  }
  if(_pp == "1"){
    digitalWrite(pp,LOW);
  }
  if(digitalRead(pir)==HIGH){
    digitalWrite(buz,HIGH);
  }
  if(digitalRead(pir)==LOW){
    digitalWrite(buz,LOW);
  }
}
