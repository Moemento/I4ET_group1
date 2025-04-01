#include <pitches.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include<Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Wifi network credentials
const char* ssid = "Galaxy A3129EC";
const char* password = "ebrahim22thmb@/@/";
// MQTT broker configuration
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "devices/IETlabconnectivity";


// Led that will be turned on/off

WiFiClient espClient;
PubSubClient client(espClient);


// Function to connect to wifi
void setup_wifi() {
  delay(10); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}
// Callback function that processes the received MQTT messages



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received[");
  Serial.print(topic); Serial.print("] ");
  
  
  // The payload of the message isprinted.
  String message;
  for (int i = 0; i < length; i++) { message+= (char)payload[i];
  }
  Serial.println(message);
  // We control the Buzzer status based on the message
  
  if (message == "0") {
    noTone(D5); // Turn off buzzer sound
    
    Serial.println("Buzzer OFF");
  } else if (message == "1") {
    
    tone(D5, 1000); //Turn on LED
    Serial.println("Buzzer ON");
  } else {
    Serial.println("Unknown command");
  }
}
  
// Reconnect to the MQTT broker if the connection is lost.
void reconnect() {
  while (!client.connected()) {
    Serial.print("Trying to connect to MQTT broker...");
    // Attempt to connect by specifying the device ID
    // IMPORTANT: this ID must be unique!
  if (client.connect("IETlabconnectivity")) {
    Serial.println("conectado!");
    // Topic subscription
    client.subscribe(mqtt_topic);
    Serial.println("Subscribed to the topic ");
  } else {
    Serial.print("connection error,error="); Serial.print(client.state());
    Serial.println(" trying again in 5 seconds");
    delay(5000);
  }
 }
}
void setup() {
  
  // Serial port configuration.
  Serial.begin(115200);
  // WiFi connection
  setup_wifi();
  // MQTT configuration
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void loop() {
  // Check if the client is connected.
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
