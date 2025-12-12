#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Soil sensor
#define SOIL_PIN 34   // Analog input only

void setup() {
  Serial.begin(115200);

  // LCD Init
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Greenhouse");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  // DHT Init
  dht.begin();
}

void loop() {
  // Read soil moisture (0–4095)
  int soilValue = analogRead(SOIL_PIN);
  
  // Convert to %
  int soilPercent = map(soilValue, 4095, 0, 0, 100);
  if (soilPercent < 0) soilPercent = 0;
  if (soilPercent > 100) soilPercent = 100;

  // Read temperature & humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if DHT failed
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT Error!");
    h = 0;
    t = 0;
  }

  // Print to Serial
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % | Temp: ");
  Serial.print(t);
  Serial.print(" C | Soil: ");
  Serial.print(soilPercent);
  Serial.println(" %");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(h, 1);
  lcd.print("% T:");
  lcd.print(t, 1);

  lcd.setCursor(0, 1);
  lcd.print("Soil:");
  lcd.print(soilPercent);
  lcd.print("%");

  delay(1000);
}
