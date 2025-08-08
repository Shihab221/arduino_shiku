#include "NewPing.h"
#include <Servo.h>
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define TRIGGER_PIN2 11
#define ECHO_PIN 12
#define MAX_DISTANCE 400	
Servo myservo; 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
	Serial.begin(9600);
  myservo.attach(9);
  myservo.write(30);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  int x= sonar.ping_cm();
	Serial.print("Distance = ");
	Serial.print(x);
	Serial.println(" cm");
  if(x<10){
    myservo.write(180);
    delay(2000);
    myservo.write(20);
  }
  else{

  }
	delay(500);

  int y= sonar2.ping_cm();
  Serial.print("Distance = ");
	Serial.print(y);
	Serial.println(" cm");
  if(y<10){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    delay(5000);
  }else{
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
}