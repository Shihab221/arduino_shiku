// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing water level
int val = 0;
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
void setup() {
	// Set D7 as an OUTPUT
   lcd.init();
  lcd.clear();         
  lcd.backlight(); 
	pinMode(sensorPower, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(sensorPower, LOW);
	pinMode(6,OUTPUT);
  pinMode(53,OUTPUT);
	Serial.begin(9600);
}

void loop() {
	//get the reading from the function below and print it
	int level = readSensor();
	
	Serial.print("Water level: ");
  // level = 12;
	Serial.println(level);
	lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Water Level:");
  
  // lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print(level);
  if(level>400){
    digitalWrite(53,HIGH);
    lcd.setCursor(0,1);
    lcd.print("BULB ON !!");
    digitalWrite(6,HIGH);
    delay(5000);
    digitalWrite(6,LOW);
    digitalWrite(53,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Motor On !!");
    delay(5000);
    digitalWrite(6,HIGH);
    digitalWrite(53,LOW);
    delay(500);
  }else{
    digitalWrite(6,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Motor OFF!");
    digitalWrite(53,LOW);
  }
	delay(1000);
}

//This is a function used to get the reading
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	val = analogRead(sensorPin);		// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// send current reading
}