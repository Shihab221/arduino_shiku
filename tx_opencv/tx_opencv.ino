// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
int ledPin4 = 13;
RH_ASK rf_driver;
void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(ledPin4, OUTPUT);
   rf_driver.init();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read the incoming data
    // Serial.println(command);
    // Perform actions based on received data
      
      if (command == '0'){
        const char *msg = "0";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        // delay(100);
        digitalWrite(ledPin4,HIGH);
      }

      else if(command == '2'){
       const char *msg = "2";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        // delay(100); 
      }

      else if(command == '3'){
       const char *msg = "3";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        // delay(100); 
      }
      else if(command == '4'){
       const char *msg = "4";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        // delay(100); 
      }

      else if(command == '5'){
       const char *msg = "5";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        // delay(100); 
      }
      else {
        const char *msg = "0";
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        // delay(100);
      }
  }
}
