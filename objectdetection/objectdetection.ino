#include <LiquidCrystal.h>

// Initialize the LCD
// RS -> D7, E -> D8, D4 -> D9, D5 -> D10, D6 -> D11, D7 -> D12
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int irSensorPin = 2;  // IR sensor connected to D2
int objectCount = 0;
bool objectDetected = false;

void setup() {
  // Initialize the LCD and print a message.
  lcd.begin(16, 2);  // 16 columns and 2 rows
  lcd.print("Object Count:");
  Serial.begin(9600);

  // Setup IR sensor pin
  pinMode(irSensorPin, INPUT);
}

void loop() {
  int irSensorState = digitalRead(irSensorPin);

  // Detect object when the IR sensor output goes LOW (object blocks the IR)
  if (irSensorState == LOW && !objectDetected) {
    objectDetected = true;
    objectCount++;  // Increment count
    lcd.setCursor(0, 1);  // Move cursor to second line
    lcd.print("Count: ");
    lcd.print(objectCount);
    Serial.println(objectCount);  // Display the object count
  }

  // Reset detection state when the object passes
  if (irSensorState == HIGH && objectDetected) {
    objectDetected = false;
  }

  delay(100);  // Debounce delay
}