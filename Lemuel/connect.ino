#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi Configuration
const char* ssid = "Livebox6-B35F";
const char* password = "4ntkh5hfdHPL";

// MQTT Configuration
const char* mqtt_server = "test.mosquitto.org"; // or your MQTT broker
const int mqtt_port = 1883;
const char* mqtt_topic = "mpu/platform";
const char* mqtt_client_id = "esp_stabilizer";

const char* mqttUser = ""; 
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_topic, mqttUser, mqttPassword ))
      Serial.println("connected");
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Must match Uno's baud rate
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

