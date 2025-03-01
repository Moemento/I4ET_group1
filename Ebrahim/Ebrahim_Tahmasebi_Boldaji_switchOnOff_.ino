int ledPin = 2;                                     // Assign the pin number(2) to the variable of ledPin

void setup() {                                      // the main function 
    pinMode(ledPin, OUTPUT);                        // Set ledPin as output
    Serial.begin(9600);                             // Start serial communication
}

void loop() 
{                                                   // the loop function
    if (Serial.available() > 0) 
    {                                               // Check if data is available in serial buffer ==> when the input value is more than 0 the condition will be startes
        char character = Serial.read();             // Read the character
        
        if (character == 'D')
        {                                           // first condition for turning on the LED
            digitalWrite(ledPin, HIGH);             // Turn LED ON
            Serial.println("LED is ON");            // print
        } 
        else if (character == 'I') 
        {                                           // second condition for turning on the LED
            digitalWrite(ledPin, LOW);              // Turn LED OFF
            Serial.println("LED is OFF");           // print
        }
    }
}
