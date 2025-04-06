#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NewPingESP8266.h>

// WiFi credentials
const char* ssid = "TGIF";                // <-- Replace with your WiFi SSID
const char* password = "anfp5132";        // <-- Replace with your WiFi password

// MQTT broker
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "iot/distance";
const char* control_topic = "iot/buzzerControl";
const char* status_topic = "iot/buzzerStatus"; // optional

WiFiClient espClient;
PubSubClient client(espClient);

// Ultrasonic sensor + buzzer pins
#define TRIGGER_PIN D1
#define ECHO_PIN D2
#define BUZZER_PIN D3
#define MAX_DISTANCE 200

NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool buzzerEnabled = true;

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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ✅ ACTUATOR CONTROL SECTION — Controls buzzer via MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String command = "";
  for (unsigned int i = 0; i < length; i++) {
    command += (char)payload[i];
  }

  command.trim();       // Remove whitespace
  command.toUpperCase(); // Ensure consistency

  Serial.print("Command received: ");
  Serial.println(command);

  if (command == "MUTE") {
    buzzerEnabled = false;
    digitalWrite(BUZZER_PIN, LOW); // Immediately stop buzzer
    client.publish(status_topic, "MUTED");
  } else if (command == "UNMUTE") {
    buzzerEnabled = true;
    client.publish(status_topic, "UNMUTED");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client_DistanceSensor")) {
      Serial.println("connected");
      client.subscribe(control_topic); // Subscribe to buzzer control topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  String distanceStr = String(distance);
  client.publish(mqtt_topic, distanceStr.c_str());

  if (buzzerEnabled && distance > 0 && distance <= 50) {
    int beepDelay = map(distance, 50, 5, 1000, 100);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(beepDelay);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

int getDistance() {
  unsigned int us = sonar.ping();
  return us / US_ROUNDTRIP_CM;
}
