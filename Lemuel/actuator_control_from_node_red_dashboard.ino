const int actuatorPin = D6; // Example pin for servo/motor

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Received actuator command: ");
  Serial.println(message);

  if (message == "left") {
    digitalWrite(actuatorPin, LOW);  // Example
  } else if (message == "right") {
    digitalWrite(actuatorPin, HIGH); // Example
  }
}

void setup() {
  // ... previous setup
  pinMode(actuatorPin, OUTPUT);
  client.setCallback(callback);
}
