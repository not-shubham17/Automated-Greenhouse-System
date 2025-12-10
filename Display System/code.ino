#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

#define SOIL_PIN 34   // ADC pin for soil sensor

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Calibrated values (adjust after checking raw values)
int wetValue = 1500;    // Raw value when sensor is fully wet
int dryValue = 3200;    // Raw value when sensor is completely dry

void setup() {
  Serial.begin(115200);

  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Greenhouse Sys");
  delay(1500);
  lcd.clear();
}

void loop() {

  // ---- Read Soil Moisture ----
  int rawSoil = analogRead(SOIL_PIN);

  // Convert raw soil value to percentage
  int soilPercent = map(rawSoil, wetValue, dryValue, 100, 0);

  // Clamp values within 0–100%
  if (soilPercent > 100) soilPercent = 100;
  if (soilPercent < 0) soilPercent = 0;

  // ---- Read DHT11 ----
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT read error!");
    humidity = 0;
  }

  // ---- Display on LCD ----
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil: ");
  lcd.print(soilPercent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");

  // ---- Serial Monitor ----
  Serial.print("Raw Soil Value: ");
  Serial.println(rawSoil);

  Serial.print("Soil %: ");
  Serial.println(soilPercent);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  delay(1500);
}
