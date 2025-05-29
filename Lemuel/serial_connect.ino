#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi Configuration
const char* ssid = "Livebox6-B35F";
const char* password = "4ntkh5hfdHPL";

// MQTT Configuration
const char* mqtt_server = "broker.hivemq.com";  // e.g., broker.hivemq.com or IP
const int mqtt_port = 1883;
const char* mqtt_topic = "devices/mpu@001";         // Customize for your FlowFuse dashboard

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

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect_mqtt() {
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
  Serial.begin(115200); // Used for Serial communication with Uno & debugging
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("ESP8266 ready to receive and publish pitch and roll...");
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.println("Received from Uno: " + data);

    // Publish to MQTT topic
    client.publish(mqtt_topic, data.c_str());
    Serial.println("Published to MQTT: " + data);
  }
}
