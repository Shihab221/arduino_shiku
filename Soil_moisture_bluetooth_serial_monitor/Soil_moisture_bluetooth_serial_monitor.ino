#include<SoftwareSerial.h>

const int sensor_pin = A0;	/* Soil moisture sensor O/P pin */
int relayPin = 8;
SoftwareSerial B(3,2);
int LDRPin = A2;

void setup() {
  Serial.begin(9600);	/* Define baud rate for serial communication */
  B.begin(9600);
  B.print("Ready to start");
  pinMode(relayPin,OUTPUT);
  pinMode(LDRPin, INPUT);
}

void loop() {
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  B.print("Moisture percentage:");
  B.println(moisture_percentage);
  int LDRValue = analogRead(LDRPin);
  
  // moisture_percentage= 30;
  if(moisture_percentage<40){
    digitalWrite(8,LOW);
    B.println("Moisture Low. Possibility of Blight Disease. Motor on!!");
  }
  else if(moisture_percentage>40 && moisture_percentage<60){
    digitalWrite(8,HIGH);
    B.println("Moisture normal. Motor off !!");
  } else if(moisture_percentage>60){
    digitalWrite(8,HIGH);
    B.println("Moisture Too High. Possibility of Bacterial attack");
  }

  if(LDRValue>700){
    Serial.println(LDRValue);
    B.println("LOW LIGHT ALERT !!");
    B.println("Possibility of Powedery Mildew / Leaf Spot/ Leaf Blight Disease");
  }else{
    Serial.println(LDRValue);
    B.println("HIGH LIGHT ALERT !!");
    B.println("Possibility of Sun Burn/ Leaf Schorching /Wilting Disease");
  }
  

  delay(1000);
}
