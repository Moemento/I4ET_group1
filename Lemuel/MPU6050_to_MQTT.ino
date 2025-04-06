#include <Wire.h>
#include <MPU6050_light.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

MPU6050 mpu;
WiFiClient espClient;
PubSubClient client(espClient);

// Replace with your WiFi and MQTT credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "YOUR_MQTT_BROKER_IP"; // FlowFuse MQTT broker or other

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      // You can subscribe to actuator topics here if needed
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);  // SDA, SCL for ESP8266
  mpu.begin();
  mpu.calcGyroOffsets(true);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  mpu.update();

  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();
  float angle = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  char msg[50];
  snprintf(msg, sizeof(msg), "{\"heel\":%.2f}", angle);
  client.publish("platform/tilt", msg);  // Publish to MQTT topic

  delay(500);
}
