//Define o tom (frequência em Hz) das notas.

const int T_C = 262;
const int T_D = 294;
const int T_E  = 330;
const int T_F = 349;
const int T_G = 392;
const int T_A = 440;
const int T_B = 493;

/*
C - Dó
D - Ré
E - Mi
F - Fá
G - Sol
A - Lá
B - Si
*/

//Define o pino digital da tecla.

const int C = 11;
const int D = 10;
const int E = 9;
const int F = 8;
const int G = 7;
const int A = 6;
const int B = 5;

const int Buzz = 4;
const int LED = 13;

void setup(){
  
  //Define os pinos das teclas como entrada de dados, e o pino do LED como saída de dados.
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(C, INPUT);
  digitalWrite(C,HIGH);
  
  pinMode(D, INPUT);
  digitalWrite(D,HIGH);
  
  pinMode(E, INPUT);
  digitalWrite(E,HIGH);
  
  pinMode(F, INPUT);
  digitalWrite(F,HIGH);
  
  pinMode(G, INPUT);
  digitalWrite(G,HIGH);
  
  pinMode(A, INPUT);
  digitalWrite(A,HIGH);
  
  pinMode(B, INPUT);
  digitalWrite(B,HIGH);

   digitalWrite(LED,LOW);
}

void loop(){
  
  //Enquanto a tecla está clicada(LOW) inicia o som e acende o LED.
  
  while(digitalRead(C) == LOW){
    tone(Buzz,T_C);
    digitalWrite(LED,HIGH);
    Serial.println("C");
  }

  while(digitalRead(D) == LOW)
  {
    tone(Buzz,T_D);
    digitalWrite(LED,HIGH);
    Serial.println("D");
  }

  while(digitalRead(E) == LOW)
  {
    tone(Buzz,T_E);
    digitalWrite(LED,HIGH);
    Serial.println("E");
  }

  while(digitalRead(F) == LOW)
  {
    tone(Buzz,T_F);
    digitalWrite(LED,HIGH);
    Serial.println("F");
  }

  while(digitalRead(G) == LOW)
  {
    tone(Buzz,T_G);
    digitalWrite(LED,HIGH);
    Serial.println("G");
  }

  while(digitalRead(A) == LOW)
  {
    tone(Buzz,T_A);
    digitalWrite(LED,HIGH);
    Serial.println("A");
  }

  while(digitalRead(B) == LOW)
  {
    tone(Buzz,T_B);
    digitalWrite(LED,HIGH);
    Serial.println("B");
  }

  noTone(Buzz);
  digitalWrite(LED,LOW);
}
