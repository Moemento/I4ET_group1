#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>


Adafruit_MPU6050 mpu;

const int trigPin = 2;
const int echoPin = 4;
const int buzzerPin = 7;

Servo rollServo;   // Controls roll
Servo pitchServo;  // Controls pitch

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Wait for serial console

  Serial.println("Initializing MPU6050...");
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  Serial.println("MPU6050 Connected!");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Set sensor configuration (optional tuning)
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Attach servos
  rollServo.attach(10);   // Roll axis
  pitchServo.attach(9);  // Pitch axis

  // Center servos
  rollServo.write(90);
  pitchServo.write(90);

  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate pitch and roll angles (in degrees)
  float pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;
  float roll  = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;

  // Map angles from ±45° to 0–180° servo range
  float pitchServoAngle = map(pitch, 90, -90, 0, 180);
  float rollServoAngle  = map(roll, 90, -90, 0, 180);

  // Limit output to servo range
  pitchServoAngle = constrain(pitchServoAngle, 0, 180);
  rollServoAngle  = constrain(rollServoAngle, 0, 180);

  // Move servos
  pitchServo.write(pitchServoAngle);
  rollServo.write(rollServoAngle);

  // Debug output
 
  Serial.print(pitch, 1);
  Serial.print(",");

 
  Serial.print(roll, 1);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  float distance = duration * 0.034 / 2;

  Serial.print(",");
  Serial.println(distance);
  

  // Turn on buzzer if distance < 100 cm
  if (distance < 100) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }


}