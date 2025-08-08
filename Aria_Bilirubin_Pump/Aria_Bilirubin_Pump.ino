#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
RH_ASK rf_driver;

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(A0,INPUT); //IR
  pinMode(8,OUTPUT); //FAN
  pinMode(9,OUTPUT); //FAN
  pinMode(10,OUTPUT); //FAN SPEED
  pinMode(11,OUTPUT);
     rf_driver.init();
     pinMode(13,OUTPUT);
}

void loop() {  
  int sensorValue = analogRead(A0);
  // Serial.println(sensorValue);
  sensorValue = 80;
   if (sensorValue < 180) {
    int x = random(10,17); 
    digitalWrite(7, HIGH); 

    while (x >= 7) {
      Serial.println("D HIGH, PUMP ON");
      // Serial.println(x);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("D:");
      lcd.print(x);
      lcd.print(" Motor on!!");
      Serial.print("Motor on!!");
      lcd.setCursor(0,1);
      lcd.print("FAN ON !!");
      Serial.println("FAN ON ");
      Serial.print("");
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      analogWrite(10,150);
      delay(2000); 
      x--; 
    }

    
    lcd.setCursor(0,0);
    lcd.print("D:6");
    delay(1300);
     lcd.setCursor(0,0);
    lcd.print("D:5");
    delay(1200);
    digitalWrite(13,HIGH);
    const char *msg = "5";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
    delay(1000);
    
    digitalWrite(7, HIGH); 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PUMP OFF");
    Serial.print("PUMP OFF");
    lcd.setCursor(0,1);
    lcd.print("FAN OFF ");
    // Serial.println("Motor is off");
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    analogWrite(10,0);
    
    delay(3000);
    digitalWrite(13,LOW);
    
  }
  else{
    digitalWrite(7,HIGH);
    lcd.setCursor(0,0);   
    Serial.println("Diabetes LOW, Insuline Pump is OFF");
  lcd.print("D 0, PUMP OFF");
  lcd.setCursor(0,1);
    lcd.print("FAN OFF ");
   digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  analogWrite(10,0);
  }
  
  lcd.setCursor(2,1);  
  lcd.print("");
  delay(100);
}
