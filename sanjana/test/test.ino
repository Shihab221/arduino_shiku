// Define motor driver pins
#define ENA 2  // PWM pin for motor A speed control
#define IN1 3  // Motor A direction pin 1
#define IN2 4  // Motor A direction pin 2
#define ENB 7 // PWM pin for motor B speed control
#define IN3 5  // Motor B direction pin 1
#define IN4 6  // Motor B direction pin 2

// Define IR sensor pin
#define IR_SENSOR A0
const int pinPM25 = 9;
const int pinPM1 = 8;
const unsigned long sampleTime = 2000;  // Reduced to 2 seconds for faster updates

float calc_low_ratio(float lowPulse) {
  return lowPulse / sampleTime * 100.0;  // low ratio in %
}

float calc_c_mgm3(float lowPulse) {
  float r = calc_low_ratio(lowPulse);
  float c_mgm3 = 0.00258425 * pow(r, 2) + 0.0858521 * r - 0.01345549;
  return max(0, c_mgm3);
}

float calc_c_pcs283ml(float lowPulse) {
  float r = calc_low_ratio(lowPulse);
  float c_pcs283ml =  625 * r;
  return min(c_pcs283ml, 12500);
}
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // Set motor driver pins as output
    lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Set IR sensor pin as input
  pinMode(IR_SENSOR, INPUT);
  
  // Start serial communication for debugging
  Serial.begin(9600);
  pinMode(pinPM25, INPUT);
  pinMode(pinPM1, INPUT);
  pinMode(10,OUTPUT);
  Serial.println("Warming up...");
  digitalWrite(10,HIGH);
  delay(5000);  // 1 minute warm-up
}

void loop() {
    static unsigned long t_start = millis();
  static float lowPM = 0;

  unsigned long pulseDuration = pulseIn(pinPM25, LOW, 100000); // 100 ms timeout
  if (pulseDuration > 0) {
    lowPM += pulseDuration / 1000.0; // Accumulate pulse duration
  }

  if ((millis() - t_start) >= sampleTime) {
    float lowRatio = calc_low_ratio(lowPM);
     lcd.setCursor(0,0);
      lcd.print("Dust: ");
      lcd.print(lowRatio);
      lcd.print(" ug");
    if (lowRatio < 0.1) {
      Serial.println("No significant dust detected.");
    } else {
      Serial.print("low_%  PM    : ");
      Serial.println(lowRatio);
     
      Serial.print("c_mgm3 PM    : ");
      Serial.println(calc_c_mgm3(lowPM));
      Serial.print("c_pcs283ml PM: ");
      Serial.println(calc_c_pcs283ml(lowPM));
      Serial.println();
    }

    if(lowRatio>0.8){
    lcd.setCursor(0,1);
    lcd.print("High");
    lcd.setCursor(9,1);
    lcd.print("Mop on!");
    digitalWrite(10,LOW);
    delay(1800);
    digitalWrite(10,HIGH);
  moveForward();
  delay(400);
  stopMotors();
  delay(600);
  moveBackward();
  delay(400);
  stopMotors();
  delay(600); 


    moveForward();
  delay(400);
  stopMotors();
  delay(600);
  moveBackward();
  delay(400);
  stopMotors();
  delay(600); 

    moveForward();
  delay(400);
  stopMotors();
  delay(600);
  moveBackward();
  delay(400);
  stopMotors();
  delay(600); 
  }else{
    digitalWrite(10,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Low Dust");
    lcd.setCursor(9,1);
    lcd.println("Mop OFF");
  }

    lowPM = 0;
    t_start = millis();
  }
  


}

// Function to move forward
void moveForward() {
  analogWrite(ENA, 200); // Set speed for motor A
  analogWrite(ENB, 130); // Set speed for motor B
  digitalWrite(IN1, HIGH); // Set motor A forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Set motor B forward
  digitalWrite(IN4, LOW);
  Serial.println("going forward");
}

// Function to move backward
void moveBackward() {
  analogWrite(ENA, 200); // Set speed for motor A
  analogWrite(ENB, 130); // Set speed for motor B
  digitalWrite(IN1, LOW);  // Set motor A backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Set motor B backward
  digitalWrite(IN4, HIGH);
  Serial.println("going backward");
}

// Function to stop motors
void stopMotors() {
  analogWrite(ENA, 0); // Stop motor A
  analogWrite(ENB, 0); // Stop motor B
}
