// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
}
 
void loop()
{
    // Set buffer to size of expected message + 1 for null termination
    uint8_t buf[2];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
        // Ensure the buffer is null-terminated
        buf[buflen] = '\0';

        // Print the received message
        Serial.print("Message Received: ");
        Serial.println((char *)buf);

        // Convert the received message to an integer
        int x = atoi((char *)buf);

        if (x == 5)
        {
            //forward
            digitalWrite(13, HIGH);
            Serial.println("LED On");
            digitalWrite(4,HIGH);
            digitalWrite(5,LOW);
            digitalWrite(6,HIGH);
            digitalWrite(7,LOW);
            delay(1500);
            digitalWrite(4,LOW);
            digitalWrite(5,LOW);
            digitalWrite(6,LOW);
            digitalWrite(7,LOW);
        }
        else if(x == 4)
        {
          //reverse
            digitalWrite(13, LOW);
            Serial.println("LED Off");
            digitalWrite(4,LOW);
            digitalWrite(5,HIGH);
            digitalWrite(6,LOW);
            digitalWrite(7,HIGH);
        }
        else if(x==3){
          //turn left
          digitalWrite(4,LOW);
            digitalWrite(5,LOW);
            digitalWrite(6,HIGH);
            digitalWrite(7,LOW);
        }

        else if(x==2){
          //turn right
          digitalWrite(4,HIGH);
            digitalWrite(5,LOW);
            digitalWrite(6,LOW);
            digitalWrite(7,LOW);
        }
        else if(x == 0){
          //stop
          digitalWrite(4,LOW);
            digitalWrite(5,LOW);
            digitalWrite(6,LOW);
            digitalWrite(7,LOW);
        }
        else {
          digitalWrite(4,LOW);
            digitalWrite(5,LOW);
            digitalWrite(6,LOW);
            digitalWrite(7,LOW);
        }
    } 
}



