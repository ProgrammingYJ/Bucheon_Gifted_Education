#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

RF24 radio(7, 8);  // CE 핀: 7번, CSN 핀: 8번
const byte address[6] = "00001";  // 송신부와 동일한 주소
int LM_pin = 2;  // 소리 감지 센서 핀
bool payload = false;  // 수신할 데이터

SoftwareSerial BTSerial(3, 4);  // 블루투스 통신 핀 (3: TX, 4: RX)

void setup() {
  Serial.begin(9600);         // 디버깅용 시리얼
  BTSerial.begin(9600);       // 블루투스 통신
  pinMode(LM_pin, INPUT);     // 소리 감지 센서 입력 설정
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // 패킷 수신 처리
  if (radio.available()) {  // 데이터 수신 확인
    radio.read(&payload, sizeof(payload));  // 데이터 읽기
    if (payload) {  // 데이터 값이 true인 경우
      BTSerial.println("sound from sender");  // 블루투스로 "Sound" 전송
      Serial.println("SD");
    }
  }

  // 소리 감지 처리
  if (digitalRead(LM_pin) == HIGH) {  // 소리 감지
    BTSerial.println("sound from getter");  // 블루투스로 "Sound" 전송
    Serial.println("ISD");
    delay(100);  // 안정화 시간
  }
}

