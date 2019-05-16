// mqtt with esp32 NodeMcu

#include <WiFi.h>
#include <PubSubClient.h>

#define DEBUG
#define CONNECTED 2

#define RELE 15   //pins
#define LED 4

//informações da rede WIFI
const char* ssid = "10 real por minuto";        //WIFI SSID
const char* password =  "";      //WIFI password

const char* mqttServer = "m15.cloudmqtt.com";       //server
const char* mqttUser = "wdpvrxmh";           //user
const char* mqttPassword = "KDuQXhS68Vke";     //password
const int mqttPort = 19042;                    //port

// TOPICS
const char* mqttTopicSub1 ="rele";
const char* mqttTopicSub2 ="led";

 
WiFiClient espClient;
PubSubClient client(espClient);


void sub(){
  // add here the subscibe line for all your topics
  client.subscribe(mqttTopicSub1);
  client.subscribe(mqttTopicSub2);
}
 
void setup() {
 
  Serial.begin(115200);

  // esp32 onboard led will turn on if everything is worcking properly
  pinMode(CONNECTED, OUTPUT);

  pinMode(RELE, OUTPUT);
  pinMode(LED, OUTPUT);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG
    Serial.println("Connecting to WiFi..");
    #endif
  }
  #ifdef DEBUG
  Serial.println("Connected to WiFi");
  #endif
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    #ifdef DEBUG
    Serial.println("Connecting to MQTT Broker...");
    #endif
 
    if (client.connect("ESP32", mqttUser, mqttPassword )) {
      #ifdef DEBUG
      Serial.println("Connected");  
      #endif
 
    } else {
      #ifdef DEBUG 
      Serial.print("connection failed  ");
      Serial.print(client.state());
      #endif
      delay(2000);
 
    }
  }
  sub(); //subscribe in the topics
}



 
void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strMSG = String((char*)payload);

  #ifdef DEBUG
  Serial.print("Mensage from topic: ");
  Serial.println(topic);
  Serial.print("Mensage:");
  Serial.print(strMSG);
  Serial.println();
  Serial.println("-----------------------");
  #endif

  if(strcmp(topic,mqttTopicSub1)==0){
    if (strMSG == "0"){
       digitalWrite(RELE, HIGH);
    }else if (strMSG == "1"){
       digitalWrite(RELE, LOW);
    }  
  }else if(strcmp(topic,mqttTopicSub2)==0){
    if (strMSG == "0"){
       digitalWrite(LED, LOW);
    }else if (strMSG == "1"){ 
       digitalWrite(LED, HIGH); 
    }
  }
}

void reconect() {
  while (!client.connected()) {
    #ifdef DEBUG
    Serial.print("Trying to connect with MQTT Server...");
    #endif
     
    bool conectado = strlen(mqttUser) > 0 ?
                     client.connect("ESP32", mqttUser, mqttPassword) :
                     client.connect("ESP32");

    if(conectado) {
      #ifdef DEBUG
      Serial.println("Connected!");
      #endif
      sub();
    } else {
      #ifdef DEBUG
      Serial.println("Failed to connect to server.Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Trying again in 10 s");
      #endif
      delay(10000);
    }
  }
}
 
void loop() {
  if (!client.connected()) {
    digitalWrite(CONNECTED, LOW);
    reconect();
  }
  digitalWrite(CONNECTED, HIGH);
  client.loop();
}
