#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int LM_pin = 4;     // 아두이노의 4핀을 소리감지센서 핀으로 사용
RF24 radio(7, 8); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN를 선언.
const byte address[6] = "00001"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기와 수신기가 동일한 주소로 해야됨.
void setup() {
  Serial.begin(9600);
  pinMode(LM_pin, INPUT);   // LM_pin은 입력으로 사용
  radio.begin();
  radio.openWritingPipe(address); //이전에 설정한 5글자 문자열인 데이터를 보낼 수신의 주소를 설정
  radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.
  radio.stopListening();
}

void loop() {
  const char text[] = "Sound High";
  if(digitalRead(LM_pin) == HIGH){     // 소리가 감지되면
    radio.write(&text, sizeof(text));
    delay(100);       // 0.1초간 기다림(연속입력 방지)
  }
}