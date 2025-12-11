/**************************************************
 *  Automated Greenhouse – ESP32 + Arduino Cloud
 *  Stable Non-Blocking Version
 **************************************************/

#include <WiFi.h>
#include "thingProperties.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_PIN 34

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastRead = 0;
const long sensorInterval = 2000;   // 2 sec

void setup() {
  Serial.begin(115200);

  delay(2000);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Greenhouse Boot");
  delay(1500);
  lcd.clear();

  dht.begin();

  // Initialize IoT Cloud
  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Increase MQTT retries
  setDebugMessageLevel(2);
}

void loop() {
  ArduinoCloud.update();

  unsigned long current = millis();

  // Non-blocking sensor update
  if (current - lastRead >= sensorInterval) {
    lastRead = current;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    int soilRaw = analogRead(SOIL_PIN);
    int soilPercent = map(soilRaw, 4095, 1500, 0, 100);
    soilPercent = constrain(soilPercent, 0, 100);

    if (!isnan(h) && !isnan(t)) {
      humidity = h;
      temperature = t;
      soil = soilPercent;

      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" | Temp: ");
      Serial.print(t);
      Serial.print(" | Soil: ");
      Serial.println(soilPercent);
    }

    // Update LCD (fast + non-blocking)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print("C H:");
    lcd.print(humidity);

    lcd.setCursor(0, 1);
    lcd.print("Soil:");
    lcd.print(soilPercent);
    lcd.print("%");
  }
}
