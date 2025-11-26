#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '3', '3', '+' },
  { '4', '5', '6', '-' },
  { '7', '8', '9', '*' },
  { 'C', '0', '=', '/' }
};
byte rowPins[ROWS] = { 2, 3, 4, 5 };
byte colPins[COLS] = { 6, 7, 8, 9 };
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String password = "345";
String input = "";
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  Serial.println("Enter Password:");
}

void loop() {
  char key = kpd.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {
      input += key;
      Serial.print(key);
    }
  
    if (key == '=') {
      if (input == password) {
        Serial.println("\nWelcome");
        digitalWrite(ledPin, HIGH);
      } else {
        Serial.println("\nWrong");
        digitalWrite(ledPin, LOW);
      }
      input = "";
      Serial.println("Enter Password:");
    }
  }
}
