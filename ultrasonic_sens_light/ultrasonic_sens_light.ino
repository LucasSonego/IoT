// toggle a light with a ultrasonic sensor
// created by Lucas Sonego


#include <NewPing.h>

#define LIGHT_PIN    2
#define TRIGGER_PIN  11
#define ECHO_PIN     10
#define MAX_DISTANCE 200

#define ACTIVATION_DISTANCE 15 // distance(cm) to toggle the light

#define TIME_ON 60    //time(seconds) for the light turn off automatically

#define CLOCK 5          //amount of times per second the sensor operates

#define DEL (1000/CLOCK)

unsigned int distance;
unsigned int on_off; // on / off '-'
unsigned int time;  // time counter
unsigned int sec;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
    pinMode(LIGHT_PIN, OUTPUT);
    Serial.begin(9600);
    on_off = 0;
}

void loop() {
    delay(DEL);
    if(on_off == 0){
        ping();
    }else{
        time_count();
        ping();
    }
}

// toggle the light
void toggle_light(){
    if(on_off==1){
        on_off = 0;
        digitalWrite(LIGHT_PIN, LOW);
        
    }else{
        on_off = 1;
        digitalWrite(LIGHT_PIN, HIGH);
    }
    time = 0;
    
    delay(1000);
}

// time counter
void time_count(){
    if(sec>=CLOCK){
        sec = 0;
        time++;
    }else{
        sec++;
    }
    if(time>=(TIME_ON-1)){
        time = 0;
        toggle_light();
    }
}

// measure the distance and call toggle_light if distance < ACTIVATION_DISTANCE
void ping(){
    distance = sonar.ping_cm();
    Serial.println(distance);
    if((distance<=ACTIVATION_DISTANCE)&&(distance>0)){
        toggle_light();
    }

}
