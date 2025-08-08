#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "Pixel22";
const char* password = "shihab22";

// ThingSpeak API
unsigned long myChannelNumber = 2743183;
const char* myWriteAPIKey = "3HM51CE0OIHUIVRH";

// GPIO pins for DS18B20 sensors and DHT22 sensor
#define DS18B20_PIN1 D1
#define DS18B20_PIN2 D2
#define DS18B20_PIN3 D3
#define DS18B20_PIN4 D4
#define DHT_PIN D5

// Initialize DHT22 sensor
#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

// Initialize OneWire and DallasTemperature for DS18B20
OneWire oneWire1(DS18B20_PIN1);
OneWire oneWire2(DS18B20_PIN2);
OneWire oneWire3(DS18B20_PIN3);
OneWire oneWire4(DS18B20_PIN4);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);
DallasTemperature sensors4(&oneWire4);

// WiFi and ThingSpeak setup
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Initialize sensors
  dht.begin();
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  sensors4.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Request temperature readings from each DS18B20 sensor
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();
  sensors3.requestTemperatures();
  sensors4.requestTemperatures();

  // Read temperatures from DS18B20 sensors
  float temp1 = sensors1.getTempCByIndex(0);
  float temp2 = sensors2.getTempCByIndex(0);
  float temp3 = sensors3.getTempCByIndex(0);
  float temp4 = sensors4.getTempCByIndex(0);

  // Read temperature and humidity from DHT22 sensor
  float dhtTemperature = dht.readTemperature();
  float dhtHumidity = dht.readHumidity();

  // Check for DHT22 reading errors
  if (isnan(dhtTemperature) || isnan(dhtHumidity)) {
    Serial.println("Failed to read from DHT22 sensor!");
    dhtTemperature = 0;
    dhtHumidity = 0;
  }

  // Print readings to Serial
  Serial.print("DS18B20 Sensor 1: "); Serial.println(temp1);
  Serial.print("DS18B20 Sensor 2: "); Serial.println(temp2);
  Serial.print("DS18B20 Sensor 3: "); Serial.println(temp3);
  Serial.print("DS18B20 Sensor 4: "); Serial.println(temp4);
  Serial.print("DHT22 Temperature: "); Serial.println(dhtTemperature);
  Serial.print("DHT22 Humidity: "); Serial.println(dhtHumidity);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, temp1);
  ThingSpeak.setField(2, temp2);
  // ThingSpeak.setField(3, temp3);
  // ThingSpeak.setField(4, temp4);
  ThingSpeak.setField(3, dhtTemperature);
  ThingSpeak.setField(4, dhtHumidity);

  // Write to ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.println("Problem uploading data. HTTP error code " + String(x));
  }

  // Wait 20 seconds before the next update
  delay(30000*60);
}
