void setup() {
  Serial.begin(115200);        // Serial Monitor on ESP8266
  Serial.setTimeout(50);       // Optional: adjust based on expected data rate

  // Begin UART0 used for communication with Arduino Uno (default Serial on ESP8266)
  Serial.println("ESP8266 ready to receive pitch and roll...");
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Read until newline
    Serial.println("Received from Uno: " + data);
  }
}
