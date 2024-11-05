#include <SPI.h> 
#include <nRF24L01.h>
#include <SoftwareSerial.h>
#include <RF24.h>
SoftwareSerial BTSerial (7, 8);
int LM_pin = 4;     // 아두이노의 4핀을 소리감지센서 핀으로 사용
int LED_pin = 6;    // 아두이노의 6번핀을 LED 핀으로 사용
RF24 radio(7, 8); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN 선언.
const byte address[6] = "00001";
void setup(){
  pinMode(LED_pin, OUTPUT); // LED_pin을 출력으로 사용
  pinMode(LM_pin, INPUT);   // LM_pin은 입력으로 사용
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  BTSerial.begin(9600);
}

void loop() {
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    if(digitalRead(LM_pin) == HIGH || text == "Sound High"){
      digitalWrite(LED_pin, HIGH);
      delay(100);       // 0.1초간 기다림(연속입력 방지)
      digitalWrite(LED_pin, LOW);  // LED 소등
    }
  }
}