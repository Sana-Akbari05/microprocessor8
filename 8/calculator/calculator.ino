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
String num1 = "";
String num2 = "";
char op = 0;
bool enteringSecond = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Calculator Ready. Enter numbers:");
}

void loop() {
  char key = kpd.getKey();
  if (!key) return;

  if (key == 'C') {
    num1 = "";
    num2 = "";
    op = 0;
    enteringSecond = false;
    Serial.println("Cleared");
    return;
  }

  if (key >= '0' && key <= '9') {
    if (!enteringSecond && op == 0) {
      num1 += key;
    } else {
      enteringSecond = true;
      num2 += key;
    }
    Serial.print("Input: ");
    Serial.print(num1);
    if (op) {
      Serial.print(" ");
      Serial.print(op);
      Serial.print(" ");
      Serial.print(num2);
    }
    Serial.println();
    return;
  }

  if (key == '+' || key == '-' || key == '*' || key == '/') {
    op = key;
    enteringSecond = true;
    Serial.print("Operator: ");
    Serial.println(op);
    return;
  }

  if (key == '=') {
    if (num1.length() > 0 && num2.length() > 0 && op) {
      double a = num1.toFloat();
      double b = num2.toFloat();
      double res = 0;
      bool ok = true;

      switch (op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/':
          if (b == 0) {
            Serial.println("Error: Division by zero!");
            ok = false;
          } else res = a / b;
          break;
      }

      if (ok) {
        Serial.print("Result: ");
        Serial.print(num1);
        Serial.print(op);
        Serial.print(num2);
        Serial.print('=');
        Serial.println(res);
      }
    } else {
      Serial.println("Incomplete expression!");
    }
    // آماده برای محاسبه جدید
    num1 = "";
    num2 = "";
    op = 0;
    enteringSecond = false;
  }
}
