//ESPtera lagarrrto

#include "BluetoothSerial.h"

#define LED 21

BluetoothSerial ESP_BT;

unsigned int delay1 = 0;
unsigned int ledstatus = 0;
#define BTLED 2

unsigned char sinal;


void setup() {
  Serial.begin(9600);
  ESP_BT.begin("ESPtera_Lagarrto");
  pinMode (BTLED, OUTPUT);
  pinMode (LED, OUTPUT);
}

void loop(){
  if (ESP_BT.available()){
    bt_led();
    sinal = ESP_BT.read();
    Serial.println(sinal);
    if(sinal == 70){
      digitalWrite(LED, HIGH);
      Serial.println("ligado");
    }else{
      digitalWrite(LED, LOW);
    }
  }
}


void ledzin(){
  if(ledstatus == 1){
      digitalWrite(BTLED, LOW);
      ledstatus = 0;
    }else{
      digitalWrite(BTLED, HIGH);
      ledstatus = 1;
    }
}

void bt_led(){
  if(!(ESP_BT.available())){
    digitalWrite(BTLED, LOW);
  }
  delay1++;

  if(delay1>10){
    ledzin();
    delay1 = 0;
  }
}
