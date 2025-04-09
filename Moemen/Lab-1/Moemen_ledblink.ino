void setup() {
  // Initialize the serial communication at a baud rate of 9600
  Serial.begin(9600);
  // Initialize the built-in LED as an output
  pinMode(LED_BUILTIN, OUTPUT);
  // Start with the LED off
  digitalWrite(LED_BUILTIN, HIGH);
  // Print initial request message to Serial Monitor
  Serial.println("Enter 'B' to turn LED ON and 'O' to turn LED OFF.");
}

void loop() {
  // Check if data is available in the Serial Monitor
  if (Serial.available() > 0) {
    // Read the incoming byte
    char incomingByte = Serial.read();
    // Check if the incoming byte is 'B' or 'O'
    if (incomingByte == 'B') {
      // Turn the LED on
      digitalWrite(LED_BUILTIN, LOW);
      // Print message to Serial Monitor
      Serial.println("LED is ON");
      Serial.println("Enter 'O' to turn LED OFF.");
    } else if (incomingByte == 'O') {
      // Turn the LED off
      digitalWrite(LED_BUILTIN, HIGH);
      // Print message to Serial Monitor
      Serial.println("LED is OFF");
      Serial.println("Enter 'B' to turn LED ON.");
    }
  }
}
