#include <Servo.h>
Servo servo1;
int IRL = 4;
int IRR = 3;
int G1 = 7;
int R1 = 5;
int G2 = 10;
int R2 = 11; 

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  pinMode(IRL,INPUT);
  pinMode(IRR,INPUT);
  pinMode(G1,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(G2,OUTPUT);
  pinMode(R2,OUTPUT);
}

void loop() {
  int r = digitalRead(IRL);
  int l = digitalRead(IRR);
  Serial.print("right:");
  Serial.println(r);
  Serial.print("left");
  Serial.println(l);
  
 
  if(r==0){
    servo1.write(120);
    digitalWrite(G1,HIGH);
    digitalWrite(G2,LOW);
    digitalWrite(R2,HIGH);
 
  }else if(l == 0){
    servo1.write(0);
    digitalWrite(G2,HIGH);
    digitalWrite(G1,LOW);
    digitalWrite(R1,HIGH);
  }else {
    servo1.write(60);
    digitalWrite(G2,LOW);
    digitalWrite(G1,LOW);
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
  }
  delay(100);
  
}
