#include <Servo.h>

Servo sg90;

// Pin Configuration
const int LDR1 = A0;        // Left LDR
const int LDR2 = A1;        // Right LDR
const int SERVO_PIN = 4;    // Servo PWM Pin

// System Variables
int servoPosition = 90;     // Start at center
const int errorMargin = 20; // Minimum difference to move servo (reduce jitter)
const int stepSize = 1;     // How much to move per correction

void setup() {
  Serial.begin(9600);

  sg90.attach(SERVO_PIN);
  sg90.write(servoPosition);
  delay(1000);

  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
}

void loop() {
  // Read LDR values
  int R1 = analogRead(LDR1);  
  int R2 = analogRead(LDR2);

  // Debugging
  Serial.print("LDR1: ");
  Serial.print(R1);
  Serial.print("  |  LDR2: ");
  Serial.println(R2);

  // Calculate difference
  int diff = R1 - R2;

  // If difference is small, do nothing
  if (abs(diff) > errorMargin) {

    if (diff > 0) {
      // LDR1 is brighter → move servo LEFT
      servoPosition -= stepSize;
    } else {
      // LDR2 is brighter → move servo RIGHT
      servoPosition += stepSize;
    }
  }

  // Limit servo between 0 and 180 degrees
  servoPosition = constrain(servoPosition, 0, 180);

  // Move servo
  sg90.write(servoPosition);

  delay(80);   // Small smooth delay
}
