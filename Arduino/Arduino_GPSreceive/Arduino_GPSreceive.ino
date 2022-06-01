#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN 선언.
const byte address[6] = "00001"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기과 수신기가 동일한 주소로 해야됨.
int n=1;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.

//거리가 가까운 순으로 RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX 등으로 설정할 수 있습니다.

//높은 레벨(거리가 먼 경우)은 작동하는 동안 안정적인 전압을 가지도록 GND와 3.3V에 바이패스 커패시터 사용을 권장함
  radio.startListening(); //모듈을 수신기로 설정
}
void loop() {
  String endstr = "@";
  int i=0;
  
  if (radio.available()) {
    char text[10] = "";
    radio.read(&text, sizeof(text));
    /*
    if(n%4 == 1) {
      Serial.print("Lat:");
      for(i=0;i<sizeof(text);i++) {
        Serial.print(text[i]);
        delay(100);
      }
      Serial.print('\n'); //for Test
      //Serial.print(endstr);
      delay(100);
    }
    else if(n%4 == 2) {
      Serial.print("Long:");
      for(i=0;i<sizeof(text);i++) {
        Serial.print(text[i]);
        delay(100);
      }
      Serial.print(endstr);
      delay(100);
    }
    else if(n%4 == 3) {
      Serial.print("Time:");
      for(i=0;i<sizeof(text);i++) {
        Serial.print(text[i]);
        delay(100);
      }
      Serial.print(endstr);
      delay(100);
    }
    else if(n%4 == 0) {
      Serial.print("Course:");
      
      for(i=0;i<2;i++) {
        Serial.print(text[i]);
        delay(100);
      }
      Serial.print(endstr);
      delay(100);
    }
    n=n+1;
    */
    
    Serial.print("Lat:");
    for(i=0;i<sizeof(text);i++) {
      Serial.print(text[i]);
      delay(100);
    }
    Serial.print(endstr);
    delay(100);

    char text2[10] = "";
    radio.read(&text2, sizeof(text2));
    Serial.print("Long:");
    for(i=0;i<sizeof(text2);i++) {
      Serial.print(text2[i]);
      delay(100);
    }
    Serial.print(endstr);
    delay(100);    

    char text3[4] = "";
    radio.read(&text3, sizeof(text3));
    Serial.print("Time:");
    for(i=0;i<sizeof(text3);i++) {
      Serial.print(text3[i]);
      delay(100);
    }
    Serial.print(endstr);
    delay(100);

    char text4[1] = "";
    radio.read(&text4, sizeof(text4));
    Serial.print("Course:");
    for(i=0;i<sizeof(text4);i++) {
      Serial.print(text4[i]);
      delay(100);
    }
    Serial.print(endstr);
    delay(100);
  
  }
}
