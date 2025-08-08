#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);  // RX, TX

#define RELAY1 2  // Forward Left
#define RELAY2 3  // Forward Right


void setup() {
    Serial.begin(9600);
    BTSerial.begin(9600);
    
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);

    
    stopCar();
}

void loop() {
    if (BTSerial.available()) {
        char command = BTSerial.read();
        Serial.println(command);
        controlCar(command);
    }
}

void controlCar(char cmd) {
    switch (cmd) {
        case 'B': moveForward(); break;
        case 'F': moveBackward(); break;
        case 'S': stopCar(); break;
    }
}

void moveForward() {
    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, LOW);

}

void moveBackward() {
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, HIGH);
}


void stopCar() {
    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, HIGH);

}
