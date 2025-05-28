#include <SoftwareSerial.h>
#define unoSerial Serial

void setup() {
  Serial.begin(9600);       // Serial monitor
  unoSerial.begin(115200);    // Communication with Uno
}

void loop() {
  if (unoSerial.available()) {
    String data = unoSerial.readStringUntil('\n');  // Read until newline
    Serial.print("Raw received: ");
    Serial.println(data);

    int commaIndex = data.indexOf(',');
    if (commaIndex != -1) {
      String val1 = data.substring(0, commaIndex);
      String val2 = data.substring(commaIndex + 1);

      Serial.print("Value 1: ");
      Serial.println(val1);
      Serial.print("Value 2: ");
      Serial.println(val2);
    }
  }
}
