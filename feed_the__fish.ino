#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define BLYNK_PRINT Serial

Servo myservo;
char auth[] = "";                 //ใส่ รหัส TOKEN Blynk
#define SSID        ""                                 //ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD    ""                                   //ใส่ รหัส Wifi
int sliderV2 = 0;  //เก็บค่าเป็น Global
int sliderV4 = 0;  //เก็บค่าเป็น Global

void setup() {
  Serial.begin(115200); Serial.println();
  Blynk.begin(auth, SSID, PASSWORD,"en2.cmtc.ac.th",8080);  //เชื่อมต่อ Blynk

  WiFi.begin(SSID, PASSWORD);  //เชื่อมต่อ WiFi
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  myservo.attach(D1);  //servo ขา D1
  myservo.write(0);
  Blynk.virtualWrite(V2, 0); //reset ค่าเป็น 0
  Blynk.virtualWrite(V4, 0); //reset ค่าเป็น 0
}



BLYNK_WRITE(V2) {
  sliderV2 = param.asInt();  // รับค่าจาก Blynk sliderV2 0-5
}
BLYNK_WRITE(V4) {
  sliderV4 = param.asInt();  // รับค่าจาก Blynk sliderV4 0-5
}

BLYNK_WRITE(V1){ 
  Serial.print("valueV1 : ");
  Serial.println(param.asInt());  //รับค่าเวลาจาก Blynk และแปลงให้เป็นตัวเลข
  Serial.print("SliderV2 value: ");
  Serial.println(sliderV2);
  int i;
  if(param.asInt())  
  {
      for(i = 0; i < sliderV2; i++){
      myservo.write(0);
      delay(200);
      myservo.write(15);
      delay(200);
      myservo.write(0);

      Serial.print("Feeding round: ");
      Serial.println(i + 1);  // แสดงรอบที่ให้อาหาร
      delay(1000);
     }
  }
}

BLYNK_WRITE(V3){
  Serial.print("valueV3 : ");
  Serial.println(param.asInt());  //รับค่าเวลาจาก Blynk และแปลงให้เป็นตัวเลข
  Serial.print("SliderV4 value: ");
  Serial.println(sliderV4);
  int i;
  if(param.asInt())  
  {
      for(i = 0; i < sliderV4; i++){ 
      myservo.write(0);
      delay(200);
      myservo.write(15);
      delay(200);
      myservo.write(0);
      
      Serial.print("Feeding round: ");
      Serial.println(i + 1);  // แสดงรอบที่ให้อาหาร
      delay(1000);
     }
  }
}

BLYNK_WRITE(V5) {
  Serial.print("valueV5 : ");
  Serial.println(param.asInt());  //รับค่าเวลาจาก Blynk และแปลงให้เป็นตัวเลข
  if(param.asInt())
  {
     myservo.write(0);
     delay(200);
     myservo.write(15);
     delay(200);
     myservo.write(0);
  }
}

void loop() {
  Blynk.run();
}
