#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wi-Fi credentials
const char* ssid = "Aria";        // Replace with your WiFi SSID
const char* password = "74292422";  // Replace with your WiFi password

// Telegram bot credentials
const char* BOTtoken = "7509932383:AAGqUvVh38oYKkdM9pAWD6-QWY04Ehn4rU8";  // Replace with your bot token
const char* CHAT_ID = "5896058217";  // Replace with your chat ID

// Create a WiFi client and Telegram bot instance
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(9600);  // Initialize serial for debugging and communication

  // Initialize Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up Telegram bot
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);
  bot.sendMessage(CHAT_ID, "WiFi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!", "");
}

void loop() {
  // Check if data is available on the serial port
  while (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Read a line of input from Serial
    sendTelegramMessage(data);                  // Send data to Telegram
  }
}

void sendTelegramMessage(String data) {
  // Log received data
  Serial.println("Received Data: " + data);

  // Send data to Telegram bot
  if (bot.sendMessage(CHAT_ID, "Received Data: " + data, "")) {
    Serial.println("Message sent to Telegram successfully.");
  } else {
    Serial.println("Failed to send message to Telegram.");
  }
}
