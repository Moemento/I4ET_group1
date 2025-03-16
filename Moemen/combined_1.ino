#include <NewPingESP8266.h>

#define TRIGGER_PIN D1    // Ultrasonic sensor trigger pin
#define ECHO_PIN D2       // Ultrasonic sensor echo pin
#define BUZZER_PIN D3     // Passive buzzer pin
#define MAX_DISTANCE 200  // Maximum distance to measure (in cm)

NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);  
  pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer as output
}

void loop() {
  int distance = getDistance();  // Read distance

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 50) {  // If object is detected within 50 cm
    int beepDelay = map(distance, 50, 5, 1000, 100);  
    // - At 50 cm, beep every 1 sec
    // - At 5 cm, beep every 0.1 sec (fast alert)

    tone(BUZZER_PIN, 1000);  // Activate buzzer
    delay(100);               // Short beep duration
    noTone(BUZZER_PIN);       // Stop buzzer
    delay(beepDelay);         // Adjust beep frequency
  }

  delay(200);  // Small delay before next reading
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  unsigned int us = sonar.ping();
  return us / US_ROUNDTRIP_CM;  // Convert to cm
}

