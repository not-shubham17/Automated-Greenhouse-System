#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo doorServo;

// Set your desired password
String password = "1234";  
String input_password = "";

// Keypad configuration ----------------------------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------------------------------------------------------

void setup() {
  lcd.init();
  lcd.backlight();

  doorServo.attach(10);        // Servo connected to pin 10
  doorServo.write(0);          // Door closed position

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD");
}

void loop() {

  char key = keypad.getKey();

  if (key) {
    // If user presses '#', check password
    if (key == '#') {
      checkPassword();
    }
    // If user presses '*', reset input
    else if (key == '*') {
      input_password = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENTER PASSWORD");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else {
      // Append typed key & show mask
      if (input_password.length() < 10) {
        input_password += key;

        lcd.setCursor(0, 1);
        for (int i = 0; i < input_password.length(); i++) {
          lcd.print('*');
        }
      }
    }
  }
}

void checkPassword() {
  lcd.clear();
  
  if (input_password == password) {
    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED");

    // Open door
    doorServo.write(90);
    delay(5000);  // Wait 5 seconds

    // Close door
    doorServo.write(0);

  } else {
    lcd.setCursor(0, 0);
    lcd.print("WRONG PASSWORD");
  }

  delay(2000);

  // Reset screen
  input_password = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD");
}
