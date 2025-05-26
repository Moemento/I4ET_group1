#define RED_LED 14    // GPIO14 (D5)
#define GREEN_LED 12  // GPIO12 (D6)
#define BLUE_LED 13   // GPIO13 (D7)

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
}

void loop() {
    // Turn on RED, turn off others
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay(1000);  // Wait 1 second

    // Turn on BLUE, turn off others
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    delay(1000);  // Wait 1 second

    // Turn on GREEN, turn off others
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    delay(1000);  // Wait 1 second
}
