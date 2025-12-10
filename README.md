# Automated Greenhouse System

This project is a complete, modular, and fully documented **Automated Greenhouse System** created using multiple Arduino/ESP32-based subsystems. It includes real-time monitoring, irrigation automation, environmental sensing, solar tracking, security mechanisms, and structured wiring diagrams.

---

## 📌 Overview

The Automated Greenhouse System is designed to:

* Maintain ideal soil moisture levels
* Monitor temperature and humidity
* Display sensor readings on an LCD
* Automate irrigation using a relay and pump
* Track sunlight for maximum solar efficiency
* Secure access using a keypad + servo lock system
* Use solar energy to power the system (optional)

All modules are independent and integrate into a single greenhouse model.

---

## 📂 Project Modules

### 1. **ESP32 Main Greenhouse Controller**

**Components:**

* ESP32
* Soil Moisture Sensor (Analog → GPIO34)
* DHT11 Sensor (GPIO4)
* LCD I2C (SDA → 21, SCL → 22)

**Functions:**

* Reads soil moisture (1–100%)
* Reads temperature & humidity
* Displays values on 16×2 LCD

---

### 2. **Drip Irrigation System (Arduino UNO)**

**Components:**

* Arduino UNO
* Soil moisture sensor (AO → A0)
* Relay module (IN → D3)
* Water pump
* 9–12V battery or adapter

**Functions:**

* Turns pump ON when soil moisture < 40%
* Turns pump OFF when soil moisture > 80%

---

### 3. **Security System (Arduino UNO)**

**Components:**

* Arduino UNO
* 4×4 Keypad
* Servo motor
* LCD display

**Functions:**

* Enter password to unlock
* Correct password → "WELCOME", servo opens door
* Wrong password → "WRONG PASSWORD"
* Password hidden using ***

---

### 4. **Solar Tracking System (Arduino UNO)**

**Components:**

* Arduino UNO
* 2 × LDR sensors (A0, A1)
* 2 × 10kΩ resistors
* SG90/MG995 servo motor (D4)
* Solar panel mounted on servo base

**Wiring:**

* **Servo:**

  * Signal → D4
  * VCC → 5V
  * GND → GND
* **LDR1:** 5V → LDR → Node → A0 → 10kΩ → GND
* **LDR2:** 5V → LDR → Node → A1 → 10kΩ → GND

**Functions:**

* Compares light intensity on LDRs
* Rotates servo toward brighter side
* Includes deadband to avoid jitter
* Protects servo with angle limits (0°–180°)

---

## 🛠️ Hardware Pin Mapping Summary

### **ESP32 Module**

| Component            | Pin    |
| -------------------- | ------ |
| Soil Moisture Sensor | GPIO34 |
| DHT11 Sensor         | GPIO4  |
| LCD SDA              | GPIO21 |
| LCD SCL              | GPIO22 |

### **Irrigation Module (Uno)**

| Component      | Pin |
| -------------- | --- |
| Soil Sensor AO | A0  |
| Relay IN       | D3  |

### **Security System**

| Component | Pin       |
| --------- | --------- |
| Keypad    | D2–D9     |
| Servo     | D10 (PWM) |
| LCD       | SDA/SCL   |

### **Solar Tracker**

| Component | Pin |
| --------- | --- |
| LDR1      | A0  |
| LDR2      | A1  |
| Servo     | D4  |

---

## 📦 Folder Structure

```
Automated-Greenhouse/
│
├── esp32-controller/
│   └── greenhouse_main.ino
│
├── irrigation-system/
│   └── irrigation.ino
│
├── solar-tracker/
│   └── solar_tracker.ino
│
├── security-system/
│   └── security_lock.ino
│
└── README.md
```

---

## 📈 Future Improvements

* Add Blynk/IoT dashboard
* Add dual-axis solar tracking
* Add fans + automatic ventilation control
* Add data logging (SD card or Firebase)
* Add battery charging regulation using solar

---

## 🧪 Testing & Calibration

1. Calibrate soil moisture dry/wet readings
2. Adjust servo rotation limits on solar tracker
3. Set password for security module
4. Verify LCD I2C address (0x27/0x3F)

---

## 📝 Credits

Project created by Shubham and Viraj as part of the **Automated Greenhouse** system.

---
