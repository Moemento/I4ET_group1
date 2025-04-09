#define BUZZER_PIN D3  // Buzzer pin

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int distance = getDistance();  // Get obstacle distance

  if (distance > 0 && distance < 50) {  // If object is closer than 50 cm
    int beepDelay = map(distance, 50, 5, 1000, 100);  
    // - At 50 cm, beep every 1 sec
    // - At 5 cm, beep every 0.1 sec

    tone(BUZZER_PIN, 1000);  // Start buzzer sound
    delay(100);              // Short beep duration
    noTone(BUZZER_PIN);      // Stop buzzer
    delay(beepDelay);        // Control beep frequency
  }
}

int getDistance() {
  unsigned int us = sonar.ping();  
  return us / US_ROUNDTRIP_CM; 
}
