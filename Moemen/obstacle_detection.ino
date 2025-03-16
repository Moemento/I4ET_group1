#include <NewPingESP8266.h>

#define TRIGGER_PIN D1    // Ultrasonic trigger pin
#define ECHO_PIN D2       // Ultrasonic echo pin
#define MAX_DISTANCE 200  // Max distance in cm

NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned int us = sonar.ping();  // Measure distance
  int distance = us / US_ROUNDTRIP_CM; 

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);  // Wait before next reading
}
