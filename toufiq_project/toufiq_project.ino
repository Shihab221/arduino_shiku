#include <SoftwareSerial.h>
char val=0;
void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);      // Serial Monitor
   // HC-05 default speed in communication mode
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}
void loop() {

  if (Serial.available()  > 0)
    {
      val = Serial.read();
      Serial.println(val);
      
      if (val == '1'){
        pinMode(7,LOW);
        digitalWrite(13,HIGH);
      }
      else if(val == '2'){
       pinMode(7,HIGH);
       digitalWrite(13,HIGH);
      }
      else if(val == '3'){
       pinMode(6,LOW);
       digitalWrite(13,HIGH);
      }
      else if(val == '4'){
       pinMode(6,HIGH);
       digitalWrite(13,HIGH);
      }
      else{
        pinMode(6,HIGH);
        pinMode(7,HIGH);
      }
    }
  // pinMode(7,LOW);
  // delay(3000);
  // pinMode(7,HIGH);
  // delay(2000);
}


