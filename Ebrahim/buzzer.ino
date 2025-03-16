#include <pitches.h>



// Notes in the melody
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6
};

int duration = 500;  // 500 milliseconds

void setup() {
  pinMode(1, OUTPUT); // Set the buzzer pin as an output
}

void loop() {
  //for (int thisNote = 0; thisNote < 8; thisNote++) {
    // Play the note on the buzzer    tone(D1, melody[5], duration);
    
    // Wait before playing the next note
    delay(10);
  //}

  // Pause before repeating the melody
  delay(10000);
}
