#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// ———— Wi-Fi settings ————
const char* ssid     = "TGIF";
const char* password = "anfp5132";

// ———— MQTT settings ————
// Use the broker address shown in your FlowFuse dashboard
const char* mqtt_server = "test.mosquitto.org";
const int   mqtt_port   = 1883;

// Your full MQTT username (e.g. "alice@32E4NEO5pY")
const char* mqtt_user   = "";
// The password you set when creating that client
const char* mqtt_pass   = "";

// ———— Globals ————
WiFiClient    wifiClient;
PubSubClient  mqttClient(wifiClient);
String        buffer = "";

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect_mqtt() {
  // Loop until we’re re-connected
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT…");
    // Client ID must match username on FlowFuse
    if (mqttClient.connect(mqtt_user, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println("; retrying in 5s");
      delay(5000);
    }
  }
}

void setup() {
  // Start Serial for debug & to receive from Uno
  Serial.begin(115200);
  delay(10);

  setup_wifi();

  // Point PubSubClient at your broker
  mqttClient.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Ensure MQTT stays connected
  if (!mqttClient.connected()) {
    reconnect_mqtt();
  }
  mqttClient.loop();

  // Read lines from the Uno
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      buffer.trim();
      // Simple validation
      if (buffer.startsWith("{") && buffer.endsWith("}")) {
        // Publish to FlowFuse topic
        mqttClient.publish("platform/mpu", buffer.c_str());
        Serial.print("Published: ");
        Serial.println(buffer);
      }
      buffer = "";
    } else {
      buffer += c;
    }
  }
}
