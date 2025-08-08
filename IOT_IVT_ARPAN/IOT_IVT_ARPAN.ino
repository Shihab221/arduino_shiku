
#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;
#include<Servo.h>
Servo servo;


void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  Serial.begin(9600); delay(10);
  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 5000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
  servo.attach(9);
  servo.write(30);
}

void loop() {
  
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      int i = LoadCell.getData();
      // Serial.print("Load_cell output val: ");
      // Serial.println(i);
      newDataReady = 0;
      t = millis();
    servo.write(30);
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("Weight:");
    // Serial.print("Weight:");
    Serial.println(i);

    lcd.print(i);
    lcd.setCursor(10,0);
    lcd.print("mL");// lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
    // i = 800;
    if(i<10){
     
      lcd.setCursor(0,1);
      lcd.print("Place the saline");
    }else if(i<600){
            servo.write(70);
      lcd.setCursor(0,1);
      lcd.print("LEVEL LOW    !!!  ");
      // Serial.print("Servo On");

    } else if(i>600){
 

      servo.write(30);
      lcd.setCursor(0,1);
      lcd.print("Level Normal   !!!  ");

    }
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  // check if last tare operation is complete:
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }

delay(1000);
 
}

