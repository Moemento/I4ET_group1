#include "arduino_secrets.h"

void setup() {
  Serial.begin(9600);        // Start Serial communication at 9600 baud
  pinMode(LED_BUILTIN, OUTPUT); // Set built-in LED as an output
  digitalWrite(LED_BUILTIN, HIGH); // Start with LED OFF

  Serial.println("Enter ASCII 66 ('B') to turn LED ON and ASCII 79 ('O') to turn LED OFF.");
}

void loop() {
  // Check if data is available in the Serial Monitor
  if (Serial.available() > 0) {
    char incomingByte = Serial.read(); // Read input
    int asciiValue = (int)incomingByte; // Convert character to ASCII

    Serial.print("Received ASCII: ");
    Serial.println(asciiValue); // Print ASCII value

    if (asciiValue == 66) { // ASCII for 'B'
      digitalWrite(LED_BUILTIN, LOW); // Turn LED ON
      Serial.println("LED is ON. Enter ASCII 79 ('O') to turn it OFF.");
    } 
    else if (asciiValue == 79) { // ASCII for 'O'
      digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
      Serial.println("LED is OFF. Enter ASCII 66 ('B') to turn it ON.");
    } 
    else {
      Serial.println("Invalid input. Enter ASCII 66 ('B') or ASCII 79 ('O').");
    }
  }
}
