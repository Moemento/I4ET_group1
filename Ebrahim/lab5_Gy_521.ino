#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include<Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

const char* ssid = "Galaxy A3129EC"; // Replace with your WiFi SSID
const char* password = "ebrahim22thmb@/@/"; // Replace with your WiFi password
const char* mqttServer = "test.mosquitto.org"; // Public MQTT broker
const int mqttPort = 1883;
const char* mqttUser = ""; 
const char* mqttPassword = "";

const int MPU_addr=0x68;  //This defines the I2C address of the MPU6050.
const int buzzer = 9;        // Buzzer connected to pin 8

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //A data type that holds 16-bit integers (values from -32,768 to 32,767)

int minVal=265; //These are calibration values for the accelerometer (used to convert raw readings to angles).
int maxVal=402;

double x; double y; double z; //A floating-point number for more precise

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    
    Serial.begin(115200);
    delay(100);

    // Connecting to WiFi
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Set MQTT server
    client.setServer(mqttServer, mqttPort);
    
    // Connect to MQTT broker
    connectToMQTT();

    Wire.begin();                     //Initializes the I2C bus for communication with the MPU6050 sensor.

    Wire.beginTransmission(MPU_addr);  
    Wire.write(0x6B);                //Begins communication with the sensor at I2C address 0x68
    Wire.write(0);                  //This sends 0 to the power management register, effectively waking up the sensor  
    Wire.endTransmission(true);     //Ends the communication and saves the settings

    //pinMode(buzzer, OUTPUT);
}

void connectToMQTT() {
    while (!client.connected()) {
        Serial.println("Connecting to the MQTT broker...");
        
        // Generate a unique Client ID
        String clientId = "IETlabClient-" + String(random(0xffff), HEX);
        
        // Attempt to connect
        if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
            Serial.println("Connected to MQTT broker!");
        } else {
            Serial.print("MQTT connection failed, error code: ");
            Serial.println(client.state());
            Serial.println("Retrying in 2 seconds...");
            delay(2000);
        }
    }
}

void loop() {
    
    client.loop();

    Wire.beginTransmission(MPU_addr);    
    Wire.write(0x3B);                    
    Wire.endTransmission(false);          
    Wire.requestFrom(MPU_addr, 14, true); 
    
    AcX = Wire.read() << 8 | Wire.read(); 
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    
    int xAng = map(AcX, minVal, maxVal, -90, 90);
    int yAng = map(AcY, minVal, maxVal, -90, 90);
    int zAng = map(AcZ, minVal, maxVal, -90, 90);
    
    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
    
    Serial.print("AngleX= "); Serial.println(x);
    Serial.print("AngleY= "); Serial.println(y);
    Serial.print("AngleZ= "); Serial.println(z);
    Serial.println("-----------------------------------------");


    char strX[16], strY[16], strZ[16],separator[32];  // Buffers to store formatted angle values

    sprintf(strX, "X: %.2f", x);  // Convert X angle to string
    sprintf(strY, "Y: %.2f", y);  // Convert Y angle to string
    sprintf(strZ, "Z: %.2f", z);  // Convert Z angle to string

    sprintf(separator, "************************");  // Separator line

    
    // Publish each angle value to the MQTT topic
    client.publish("devices/IETlabconnectivity", strX);
    client.publish("devices/IETlabconnectivity", strY);
    client.publish("devices/IETlabconnectivity", strZ);

    client.publish("devices/IETlabconnectivity", separator);  // Publish separator again


    

    delay(500);
    
}
