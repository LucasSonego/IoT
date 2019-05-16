#include <dht.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>


#define data_pin 5 // pino de dados

dht sensor; // objeto "dht"

int temperatura = 0x00;
#define BUZZER 7
#define TRIG 13
#define ECHO 12
#define MAX_DISTANCE 300

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);
unsigned int distance;

LiquidCrystal_I2C lcd(0x27,16,2);

byte customChar[] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
{
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.createChar(0, customChar);
}


void loop(){
  delay(250);
  dist();
  temp();
  prnt();
}

void temp(){
  sensor.read11(data_pin);
  temperatura = sensor.temperature;
  lcd.setCursor(0,1);
  lcd.print("temperatura: ");
  lcd.print(temperatura);
  Serial.println(temperatura);
  lcd.write(0);
  lcd.print("C");
}

void dist(){
  distance = sonar.ping_cm();    //centimeter
  //distance = sonar.ping_in();    //inch
}

void prnt(){
  if(distance>0){
    if(distance < 10){
      tone(BUZZER, 1000);
    }else{
      noTone(BUZZER);
    }
    
    lcd.setCursor(10,0);
    lcd.print(distance);
    lcd.print("cm   ");     //centimeter
    //lcd.print("in   ");     //inch
  }
}