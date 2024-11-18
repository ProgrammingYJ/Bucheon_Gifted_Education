#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE 핀: 7번, CSN 핀: 8번
const byte address[6] = "00001";  // 통신 주소
int LM_pin = 4;  // 소리 감지 센서 핀
bool payload = true;  // 패킷으로 전송할 데이터

void setup() {
  Serial.begin(9600);
  pinMode(LM_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

void loop() {
  if (digitalRead(LM_pin) == HIGH) {  // 소리 감지
    radio.write(&payload, sizeof(payload));  // 데이터 전송
    delay(100);  // 안정화 시간
  }
}
