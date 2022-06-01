#include <math.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

SoftwareSerial gpsSerial(5,4);
RF24 radio(7, 8);                // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN를 선언.
const byte address[6] = "00001"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기와 수신기가 동일한 주소로 해야됨.

//  gps - arduino
//  tx - 5
//  rx - 4
//  vcc - 5v
//  gnd - gnd

char c = "";
String str2 = "";
String targetStr2 = "GPRMC";

double AvgSpeed = 3; // km/h
double disresult = 0;
double CountSpeed = 2;
double ResSpeed = 0;
double Time = 0;  
double EndLat = 0;
double EndLong = 0;


void setup() {
  // put your setup code here, to run once:
  
  radio.begin();
  radio.openWritingPipe(address); //이전에 설정한 5글자 문자열인 데이터를 보낼 수신의 주소를 설정
  radio.setPALevel(RF24_PA_MIN);   //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.
  radio.stopListening();          //모듈을 송신기로 설정
  Serial.begin(9600);
  Serial.println("Start GPS... ");
  gpsSerial.begin(9600);

}

void loop() {

  char pChrBuffer[50];
  char pChrBuffer2[50];
  char pChrBuffer3[50];
  char pChrBuffer4[50];

  if(gpsSerial.available()) // gps 센서 통신 가능?
    {
      char * dtostrf(double __val, signed char __width, unsigned char __prec, char * __s);
      c=gpsSerial.read(); // 센서의 값 읽기
      if(c == '\n')
      { // \n 값인지 구분.

        if(targetStr2.equals(str2.substring(1, 6))) 
        {                                                 // NMEA 의 값이 GPRMC 일시
          
          Serial.println(str2);
        
          int first2 = str2.indexOf(",");
          int two2 = str2.indexOf(",", first2+1);
          int three2 = str2.indexOf(",", two2+1);
          int four2 = str2.indexOf(",", three2+1);
          int five2 = str2.indexOf(",", four2+1);
          int six2 = str2.indexOf(",", five2+1);
          int seven2 = str2.indexOf(",", six2+1);
          int eight2 = str2.indexOf(",", seven2+1);

          // Lat과 Long 위치에 있는 값들을 index로 추출
          String Lat = str2.substring(three2+1, four2);
          String Long = str2.substring(five2+1, six2);

          // Lat의 앞값과 뒷값을 구분
          String Lat1 = Lat.substring(0, 2);
          String Lat2 = Lat.substring(2);

          // Long의 앞값과 뒷값을 구분
          String Long1 = Long.substring(0, 3);
          String Long2 = Long.substring(3);

          // 좌표 계산.
          double LatF = Lat1.toDouble() + Lat2.toDouble()/60;
          double LongF = Long1.toDouble() + Long2.toDouble()/60;

          String Speed = str2.substring(seven2+1, eight2);
          float SpeedF = Speed.toFloat() * 1.852;

          disresult = Haversine(EndLat, EndLong, LatF, LongF);
          AvgSpeed = (AvgSpeed + SpeedF);
          ResSpeed = AvgSpeed/CountSpeed;
          Time = disresult / (ResSpeed*1000/60);
          CountSpeed++;
          Serial.print("위도 : ");
          Serial.println(LatF,6);
          Serial.print("경도 : ");
          Serial.println(LongF,6);
          Serial.print("거리 : ");
          Serial.println(disresult);
          Serial.print("예상도착시간 : ");
          Serial.println(Time);
          Serial.print("평균속력 : ");
          Serial.println(ResSpeed);
          Serial.println("-----------------------");

          dtostrf(LatF , 9, 6, pChrBuffer);
          dtostrf(LongF , 9, 6, pChrBuffer2);
          dtostrf(Time, 3, 2, pChrBuffer3);
          
          radio.write(&pChrBuffer, sizeof(pChrBuffer));
          radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
          radio.write(&pChrBuffer3, sizeof(pChrBuffer3));

          if(LatF <= 37.453769 && LatF >= 37.453207)
          {
           if(LongF <= 127.134695 && LongF >= 127.133751)
           {
              courseNum = '1';
              if(Arrdis1 >= 20)
              {
                Arrdis1 = Arrdis1 - Haversine(BefLat, BefLong, LatF, LongF);
                ArrTime = Arrdis1 / Speedmps;
                Serial.println(Arrdis1);
                Serial.print("분: ");
                Serial.println(ArrTime/60);
                //Serial.print("초: ");
                //Serial.println(ArrTime%60);
                int ArrMin = ArrTime/60;
                //int ArrSec = ArrTime%60;
                char ArrMinC[16];
                //char ArrSecC[16];
                itoa(ArrMin, ArrMinC, 10);
                //itoa(ArrSec, ArrSecC, 10);
                char Course[16];
                itoa(courseNum, Course, 10);
                radio.write(&pChrBuffer, sizeof(pChrBuffer));
                radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
                radio.write(&ArrMinC, sizeof(ArrMinC));
                radio.write(&Course, sizeof(Course));
                //radio.write(&ArrSecC, sizeof(ArrSecC));
                
              }
              else
              {
                Serial.println("곧 도착");
                //radio.write(&textarrive, sizeof(textarrive));
              }
           }
          }
          else if(LatF <= 37.453207 && LatF >= 37.451961)
          {
            if(LongF <= 127.133751 && LongF >= 127.128809)
            {
              courseNum = '2';
              if(Arrdis2 >= 20) 
              {
                Arrdis2 = Arrdis2 - Haversine(BefLat, BefLong, LatF, LongF);
                ArrTime = Arrdis2 / Speedmps;
                Serial.println(Arrdis1);
                Serial.print("분: ");
                Serial.println(ArrTime/60);
                //Serial.print("초: ");
                //Serial.println(ArrTime%60);
                int ArrMin = ArrTime/60;
                //int ArrSec = ArrTime%60;
                char ArrMinC[16];
                //char ArrSecC[16];
                itoa(ArrMin, ArrMinC, 10);
                //itoa(ArrSec, ArrSecC, 10);
                char Course[16];
                itoa(courseNum, Course, 10);
                radio.write(&pChrBuffer, sizeof(pChrBuffer));
                radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
                radio.write(&ArrMinC, sizeof(ArrMinC));
                radio.write(&Course, sizeof(Course));
                //radio.write(&ArrSecC, sizeof(ArrSecC));
                
              }
              else
              {
                Serial.println("곧 도착");
                //radio.write(&textarrive, sizeof(textarrive));
              }
            }
          }
          else if(LatF <= 37.451961 && LatF >= 37.450837)
          {
            if(LongF <= 127.128809 && LongF >= 127.127502)
            {
              courseNum = '3';
              if(Arrdis3 >= 20) 
              {
                Arrdis3 = Arrdis3 - Haversine(BefLat, BefLong, LatF, LongF);
                ArrTime = Arrdis3 / Speedmps;
                Serial.println(Arrdis3);
                Serial.print("분: ");
                Serial.println(ArrTime/60);

                int ArrMin = ArrTime/60;
                //int ArrSec = ArrTime%60;
                char ArrMinC[16];
                //char ArrSecC[16];
                itoa(ArrMin, ArrMinC, 10);
                //itoa(ArrSec, ArrSecC, 10);
                char Course[16];
                itoa(courseNum, Course, 10);
                radio.write(&pChrBuffer, sizeof(pChrBuffer));
                radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
                radio.write(&ArrMinC, sizeof(ArrMinC));
                radio.write(&Course, sizeof(Course));
                //radio.write(&ArrSecC, sizeof(ArrSecC));
              }
              else {
                Serial.println("곧 도착");
              }     
            }
          }
          else if(LatF <= 37.451603 && LatF >= 37.450837)
          {
            if(LongF <= 127.131018 && LongF >= 127.127502)
            {
              courseNum = '4';
              if(Arrdis4 >= 20) 
              {
                Arrdis4 = Arrdis4 - Haversine(BefLat, BefLong, LatF, LongF);
                ArrTime = Arrdis4 / Speedmps;
                Serial.println(Arrdis4);
                Serial.print("분: ");
                Serial.println(ArrTime/60);
                //Serial.print("초: ");
                //Serial.println(ArrTime%60);
                int ArrMin = ArrTime/60;
                //int ArrSec = ArrTime%60;
                char ArrMinC[16];
                //char ArrSecC[16];
                itoa(ArrMin, ArrMinC, 10);
                //itoa(ArrSec, ArrSecC, 10);
                char Course[16];
                itoa(courseNum, Course, 10);
                radio.write(&pChrBuffer, sizeof(pChrBuffer));
                radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
                radio.write(&ArrMinC, sizeof(ArrMinC));
                radio.write(&Course, sizeof(Course));
                //radio.write(&ArrSecC, sizeof(ArrSecC));
              }
              else {
                Serial.println("곧 도착");
              }
            }
          }
          else if(LatF <= 37.453207 && LatF >= 37.451603)
          {
            if(LongF <= 127.133751 && LongF >= 127.131018)
            {
              courseNum = '5';
              if(Arrdis5 >= 20) 
              {
                Arrdis5 = Arrdis5 - Haversine(BefLat, BefLong, LatF, LongF);
                ArrTime = Arrdis5 / Speedmps;
                Serial.println(Arrdis5);
                Serial.print("분: ");
                Serial.println(ArrTime/60);
                //Serial.print("초: ");
                //Serial.println(ArrTime%60);
                int ArrMin = ArrTime/60;
                //int ArrSec = ArrTime%60;
                char ArrMinC[16];
                //char ArrSecC[16];
                itoa(ArrMin, ArrMinC, 10);
                //itoa(ArrSec, ArrSecC, 10);
                char Course[16];
                itoa(courseNum, Course, 10);
                radio.write(&pChrBuffer, sizeof(pChrBuffer));
                radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
                radio.write(&ArrMinC, sizeof(ArrMinC));
                radio.write(&Course, sizeof(Course));
                //radio.write(&ArrSecC, sizeof(ArrSecC));
                
              }
              else
              {
                Serial.println("곧 도착");
                //radio.write(&textarrive, sizeof(textarrive));
              }
            }
          }
          else if(LatF <= 37.453769 && LatF >= 37.453207 && courseNum=='5')
          {
           if(LongF <= 127.134695 && LongF >= 127.133751)
           {
              courseNum = '6';
                Arrdis6 = Arrdis6 - Haversine(BefLat, BefLong, LatF, LongF);
                ArrTime = Arrdis6 / Speedmps;
                Serial.println(Arrdis6);
                Serial.print("분: ");
                Serial.println(ArrTime/60);
                //Serial.print("초: ");
                //Serial.println(ArrTime%60);
                int ArrMin = ArrTime/60;
                //int ArrSec = ArrTime%60;
                char ArrMinC[16];
                //char ArrSecC[16];
                itoa(ArrMin, ArrMinC, 10);
                //itoa(ArrSec, ArrSecC, 10);
                char Course[16];
                itoa(courseNum, Course, 10);
                radio.write(&pChrBuffer, sizeof(pChrBuffer));
                radio.write(&pChrBuffer2, sizeof(pChrBuffer2));
                radio.write(&ArrMinC, sizeof(ArrMinC));
                radio.write(&Course, sizeof(Course));
                //radio.write(&ArrSecC, sizeof(ArrSecC));
                
              }
              else
              {
                Serial.println("곧 도착");
                //radio.write(&textarrive, sizeof(textarrive));
              }
              
           }
          }


          /*
          Serial.print("거리 : ");
          Serial.println(disresult);
          Serial.print("속도 : ");
          Serial.println(ResSpeed);
          Serial.print("시간 : ");
          Serial.println(Time);
          delay(3000);
           */        
           delay(3000);
        }
        // str 값 초기화 
        str2 = "";
        
       }else{ // \n 아닐시, str에 문자를 계속 더하기
        str2 += c;
       }
     }
   
}

double Haversine(double x1, double y1, double x2, double y2) 
  {
    double distance;
    double radius = 6371;
    double toRadian = PI / 180;
  
    double deltaLatitude = abs(x1 - x2) * toRadian;
    double deltaLongitude = abs(y1 - y2) * toRadian;
  
    double sinDeltaLat = sin(deltaLatitude / 2);
    double sinDeltaLng = sin(deltaLongitude / 2);
    double squareRoot = sqrt(
      sinDeltaLat * sinDeltaLat + cos(x1 * toRadian) * cos(x2 * toRadian)
      * sinDeltaLng * sinDeltaLng);
  
      distance = 1000 * 2 * radius * asin(squareRoot);
      return distance;
      
  }
