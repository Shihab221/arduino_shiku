#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
LiquidCrystal_I2C lcd(0x27,16,2);  


#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  pinMode(8,OUTPUT);
  // Print a message on both lines of the LCD.
 sensors.begin();
 pinMode(13,OUTPUT);
 
}

void loop() {
  digitalWrite(13,HIGH);
   sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  int T = sensors.getTempCByIndex(0);
  delay(100);
  
   lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Temp:");
  lcd.print(T);
  lcd.print(" C");
  if(T<36){
    lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
    lcd.print("Heater On !!");
    digitalWrite(8,LOW);
  } else if(T>40){
    lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
    lcd.print("Cooling Heater");
    digitalWrite(8,HIGH);
  }else{
    lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
    lcd.print("Normal Range!!");
    digitalWrite(8,HIGH);
  }
  
  
  
}


