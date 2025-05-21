#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

// Create objects
MPU6050 mpu;
Servo servoPitch;
Servo servoRoll;

// Pin definitions
const int servoPitchPin = D9;  // Up/Down
const int servoRollPin = D10;  // Left/Right

// Orientation and timing variables
float pitch = 0, roll = 0;
unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);  // Halt if MPU not connected
  }

  servoPitch.attach(servoPitchPin);
  servoRoll.attach(servoRollPin);

  lastTime = millis();  // Initialize timer
  delay(100);  // Let the sensor stabilize
}

void loop() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;  // Convert ms to seconds
  lastTime = now;

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Compute accelerometer angles (in degrees)
  float accPitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float accRoll  = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;

  // Convert gyro readings to deg/sec (default scale ±250°/s)
  float gxDeg = gx / 131.0;
  float gyDeg = gy / 131.0;

  // Complementary filter: combine accel and gyro
  pitch = 0.98 * (pitch + gxDeg * dt) + 0.02 * accPitch;
  roll  = 0.98 * (roll  + gyDeg * dt) + 0.02 * accRoll;

  // Define max expected tilt angle
  float maxTilt = 90.0;  // degrees

  // Clamp values to prevent servo overdriving
  pitch = constrain(pitch, -maxTilt, maxTilt);
  roll  = constrain(roll, -maxTilt, maxTilt);

  // Map -45° to +45° --> 0 to 180 servo degrees
  float pitchAngle = (pitch + maxTilt) * 180.0 / (2 * maxTilt);
  float rollAngle  = (roll  + maxTilt) * 180.0 / (2 * maxTilt);

  // Send angles to servos
  servoPitch.write(pitchAngle);
  servoRoll.write(rollAngle);

  // Debug output
  Serial.print("Pitch: ");
  Serial.print(pitch, 1);
  Serial.print(" | Roll: ");
  Serial.print(roll, 1);
  Serial.print(" | Servo P: ");
  Serial.print(pitchAngle);
  Serial.print(" | Servo R: ");
  Serial.println(rollAngle);

  //delay(10);  // 100 Hz update rate
}
