void setup() {
  Serial.begin(9600);               // Start serial communication at 9600 baud
  pinMode(LED_BUILTIN, OUTPUT);       // Initialize the onboard LED pin as an output
  digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off initially (active LOW)
  Serial.println("Press 'A' to turn LED ON, 'M' to turn LED OFF");
}

void loop() {
  if (Serial.available() > 0) {       // Check if data is available on the serial port
    char inChar = Serial.read();      // Read the incoming character

    if (inChar == 'A' || inChar == 'a') {
      digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (active LOW)
      Serial.println("LED is ON");
    } 
    else if (inChar == 'M' || inChar == 'm') {
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off
      Serial.println("LED is OFF");
    }
  }
}
