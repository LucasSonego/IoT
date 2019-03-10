#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIG 13
#define ECHO 12
#define MAX_DISTANCE 300

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);
unsigned int distance;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Distance:");
}


void loop(){
  delay(250);
  dist();
  prnt();
}

void dist(){
  distance = sonar.ping_cm();    //centimeter
  //distance = sonar.ping_in();    //inch
}

void prnt(){
  if(distance>0){
    
    lcd.setCursor(10,0);
    lcd.print(distance);
    lcd.print("cm   ");     //centimeter
    //lcd.print("in   ");     //inch
  }
}
