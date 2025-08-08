#include <dht11.h>
#define DHT11PIN 8
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
dht11 DHT11;
int relay=9;
#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

//pins:
const int HX711_dout = 6; //mcu > HX711 dout pin
const int HX711_sck = 7; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

void  setup()
{
  Serial.begin(9600);
    lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  pinMode(13,OUTPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  pinMode(10,OUTPUT);

  Serial.begin(57600); delay(10);
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

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
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
 
 
}

void loop()
{
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      int i = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(i);
      newDataReady = 0;
      t = millis();
      lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
      lcd.print("Weight:");
      lcd.print(i);
      lcd.setCursor(10,0);
      lcd.print("g");
      if(i>5){
        digitalWrite(13,LOW);
      }else{
        digitalWrite(13,HIGH);
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


  //code
  Serial.println();
  // int w = 2;
  // Print a message on both lines of the LCD.
  
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
    float T = DHT11.temperature;
    float H = DHT11.humidity;
    // T= 10;
   lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("T:");
  lcd.print(T, 1);
  lcd.print("C");
  lcd.print(" H:");
  lcd.print(H, 2);
  lcd.print("%");
  delay(100);
  
  if(T>37.5){
    digitalWrite(relay,LOW);
    lcd.setCursor(12, 0);
    lcd.print("FAN ");
    digitalWrite(10,HIGH);
  }else if(T<36){
    digitalWrite(relay,HIGH);
    lcd.setCursor(12, 0);
    lcd.print("HEAT");
    digitalWrite(10,LOW);

  }else {
    lcd.setCursor(12, 0);
    lcd.print("NORM");
    digitalWrite(relay,HIGH);
    digitalWrite(10,HIGH);
  }

}



/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
   Settling time (number of samples) and data filtering can be adjusted in the config.h file
   For calibration and storing the calibration value in eeprom, see example file "Calibration.ino"

   The update() function checks for new data and starts the next conversion. In order to acheive maximum effective
   sample rate, update() should be called at least as often as the HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS.
   If you have other time consuming code running (i.e. a graphical LCD), consider calling update() from an interrupt routine,
   see example file "Read_1x_load_cell_interrupt_driven.ino".

   This is an example sketch on how to use this library
*/

// #include <HX711_ADC.h>
// #if defined(ESP8266)|| defined(ESP32) || defined(AVR)
// #include <EEPROM.h>
// #endif

// //pins:
// const int HX711_dout = 6; //mcu > HX711 dout pin
// const int HX711_sck = 7; //mcu > HX711 sck pin

// //HX711 constructor:
// HX711_ADC LoadCell(HX711_dout, HX711_sck);

// const int calVal_eepromAdress = 0;
// unsigned long t = 0;

// void setup() {
//   Serial.begin(57600); delay(10);
//   Serial.println();
//   Serial.println("Starting...");

//   LoadCell.begin();
//   //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
//   float calibrationValue; // calibration value (see example file "Calibration.ino")
//   calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
// #if defined(ESP8266)|| defined(ESP32)
//   //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
// #endif
//   EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

//   unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
//   boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
//   LoadCell.start(stabilizingtime, _tare);
//   if (LoadCell.getTareTimeoutFlag()) {
//     Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
//     while (1);
//   }
//   else {
//     LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
//     Serial.println("Startup is complete");
//   }
// }

// void loop() {
//   static boolean newDataReady = 0;
//   const int serialPrintInterval = 0; //increase value to slow down serial print activity

//   // check for new data/start next conversion:
//   if (LoadCell.update()) newDataReady = true;

//   // get smoothed value from the dataset:
//   if (newDataReady) {
//     if (millis() > t + serialPrintInterval) {
//       float i = LoadCell.getData();
//       Serial.print("Load_cell output val: ");
//       Serial.println(i);
//       newDataReady = 0;
//       t = millis();
//     }
//   }

//   // receive command from serial terminal, send 't' to initiate tare operation:
//   if (Serial.available() > 0) {
//     char inByte = Serial.read();
//     if (inByte == 't') LoadCell.tareNoDelay();
//   }

//   // check if last tare operation is complete:
//   if (LoadCell.getTareStatus() == true) {
//     Serial.println("Tare complete");
//   }

// }
