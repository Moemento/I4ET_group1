#include <Wire.h>
#include <MPU9250.h>

MPU9250 mpu;

#define RED_LED 14    // GPIO14 (D5) - Red LED
#define GREEN_LED 12  // GPIO12 (D6) - Green LED
#define BLUE_LED 13   // GPIO13 (D7) - Blue LED

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (!mpu.setup(0x68)) {  
        Serial.println("MPU connection failed!");
        while (1);
    }

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    // Set initial LED state (Green for stable)
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
}

void loop() {
    if (mpu.update()) {
        float angleX = mpu.getRoll();  // Get roll angle
        Serial.print("Angle: ");
        Serial.println(angleX);

        if (abs(angleX) > 20) {  
            // Turn on RED LED (Indicates unstable position)
            digitalWrite(RED_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        } else {
            // Keep GREEN LED on when stable
            digitalWrite(RED_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(BLUE_LED, LOW);
        }
    }
    delay(50);
}
