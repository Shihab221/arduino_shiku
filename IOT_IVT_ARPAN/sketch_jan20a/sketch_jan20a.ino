#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourWiFiSSID";         // Replace with your Wi-Fi SSID
const char* password = "YourWiFiPassword"; // Replace with your Wi-Fi password

const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "YourThingSpeakWriteAPIKey"; // Replace with your ThingSpeak Write API Key

void setup() {
  Serial.begin(9600);   // For communication with Arduino
  Serial.println();
  Serial.println("ESP32 Starting...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial.available() > 0) {  // Check if data is received from Arduino
    String data = Serial.readStringUntil('\n'); // Read data sent from Arduino
    Serial.println("Received: " + data);

    sendDataToThingSpeak(data);  // Send the received data to ThingSpeak
  }
  delay(500); // Optional: Prevent spamming ThingSpeak
}

void sendDataToThingSpeak(String value) {
  if (WiFi.status() == WL_CONNECTED) {  // Check Wi-Fi connection
    HTTPClient http;

    String url = String(server) + "?api_key=" + apiKey + "&field1=" + value;
    http.begin(url);

    int httpCode = http.GET();  // Send HTTP GET request
    if (httpCode > 0) {
      Serial.println("ThingSpeak Response: " + http.getString());
    } else {
      Serial.println("Error sending data to ThingSpeak");
    }
    http.end();  // Free resources
  } else {
    Serial.println("WiFi not connected");
  }
}
