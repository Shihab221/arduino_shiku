#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO4
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  pinMode(34,INPUT);
  sensors.begin();
}

void loop() {

  int gas = digitalRead(34);
  Serial.print("Gas");
  Serial.println(gas);
  sensors.requestTemperatures(); // Send command to get temperatures
  float tempC = sensors.getTempCByIndex(0); // Get temperature in Celsius
  float tempF = sensors.toFahrenheit(tempC); // Convert to Fahrenheit

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" °C  |  ");
  Serial.print(tempF);
  Serial.println(" °F");

  delay(1000); // Wait 1 second
}
