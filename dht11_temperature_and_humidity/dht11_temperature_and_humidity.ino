//dht11 sensor

#include <dht.h>

#define data_pin 5 // pino de dados

dht sensor; // objeto "dht"

int temperatura = 0x00,
    umidade = 0x00;
    

void setup() {
  Serial.begin(9600);
  

}

void loop() {
  sensor.read11(data_pin);
  temperatura = sensor.temperature;
  umidade = sensor.humidity;
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("\%");

  delay(2000);
}
