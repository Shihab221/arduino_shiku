#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo1;

int IRL = 3;
int IRR = 4;
int G1 = 7;
int R1 = 5;
int G2 = 10;
int R2 = 11; 

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight

  
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
    servo1.write(80);
    digitalWrite(G1,HIGH);
    digitalWrite(G2,LOW);
    digitalWrite(R2,HIGH);
    lcd.clear();
    lcd.setCursor(0, 0); // Column 0, Row 0
    lcd.print("Train on track 1!");
    lcd.setCursor(0, 1); // Column 0, Row 1
    lcd.print("Path Clear");
 
  }else if(l == 0){
    servo1.write(40);
    digitalWrite(G2,HIGH);
    digitalWrite(G1,LOW);
    digitalWrite(R1,HIGH);
    lcd.clear();
    lcd.setCursor(0, 0); // Column 0, Row 0
    lcd.print("Train on track 2!");
    lcd.setCursor(0, 1); // Column 0, Row 1
    lcd.print("Path Clear");
  }else {
    servo1.write(60);
    digitalWrite(G2,LOW);
    digitalWrite(G1,LOW);
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    lcd.clear();
    lcd.setCursor(0, 0); // Column 0, Row 0
    lcd.print("No Train!");
    lcd.setCursor(0, 1); // Column 0, Row 1
    lcd.print("");
  }
  delay(100);
  
}
