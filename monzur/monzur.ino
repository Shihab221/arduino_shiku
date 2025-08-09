#include <Servo.h>

Servo servo1;  // First servo
Servo servo2;  // Second servo

int trigPin = 6;    // Trigger
int echoPin = 7;    // Echo
#define DETECTION_THRESHOLD 500 // ~34 cm

bool objectDetected = false; // Flag to stop servos

void setup() {
  Serial.begin(9600);
  servo1.attach(8);  // Attach servo1 to pin 8
  servo2.attach(9);  // Attach servo2 to pin 9
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(11, OUTPUT); // LED or buzzer pin
}

void loop() {
  int pos1, pos2;

  // Sweep forward
  for (pos1 = 48, pos2 = 20; pos1 <= 110 && pos2 <= 160; pos1 += 2, pos2 += 5) {
    if (distance()) { // if object detected
      stopServos(pos1, pos2);
      digitalWrite(11, HIGH);
      return; // Stop loop() and freeze
    }
    digitalWrite(11, LOW);
    servo1.write(pos1);
    servo2.write(pos2);
    delay(45);
  }

  // Sweep backward
  for (pos1 = 110, pos2 = 160; pos1 >= 48 && pos2 >= 20; pos1 -= 2, pos2 -= 5) {
    if (distance()) { // if object detected
      stopServos(pos1, pos2);
      digitalWrite(11, HIGH);
      return; // Stop loop() and freeze
    }
    digitalWrite(11, LOW);
    servo1.write(pos1);
    servo2.write(pos2);
    delay(45);
  }
}

// Returns true if object detected
bool distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  if (duration > 0 && duration < DETECTION_THRESHOLD) {
    Serial.println("Object Detected!");
    digitalWrite(11, HIGH);
    delay(2000);
    digitalWrite(11, LOW);
    return true;
  } else {
    Serial.println("No Object");
    digitalWrite(11, LOW);
    return false;
  }
}

// Stops servos at current positions
void stopServos(int pos1, int pos2) {
  servo1.write(pos1);
  servo2.write(pos2);
  Serial.println("Servos Stopped!");
  while (true) {
    // Infinite loop to freeze position
    delay(100);
  }
}
