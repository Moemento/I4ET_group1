#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

MPU6050 mpu;

Servo servoPitch;
Servo servoRoll;

int pitchServoPin = D9;
int rollServoPin = D10;

// PID variables for pitch
float pitchKp = 5.0, pitchKi = 0.05, pitchKd = 1.5;
float pitchError, pitchPrevError = 0, pitchIntegral = 0;

// PID variables for roll
float rollKp = 5.0, rollKi = 0.05, rollKd = 1.5;
float rollError, rollPrevError = 0, rollIntegral = 0;

// Complementary filter vars
float accPitch, accRoll;
float gyroPitch = 0, gyroRoll = 0;
float fusedPitch = 0, fusedRoll = 0;

unsigned long lastTime;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);  // SDA, SCL

  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  servoPitch.attach(pitchServoPin);
  servoRoll.attach(rollServoPin);

  lastTime = millis();
  Serial.println("PID Gimbal Stabilizer Ready");
}

void loop() {
  // Time delta
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // Read sensor
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert to angles
  accPitch = atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI;
  accRoll  = atan2(ay, sqrt(ax * ax + az * az)) * 180 / PI;

  // Gyroscope integration (convert to deg/s, then integrate)
  gyroPitch += (gy / 131.0) * dt;
  gyroRoll  += (gx / 131.0) * dt;

  // Complementary filter
  fusedPitch = 0.98 * (fusedPitch + (gy / 131.0) * dt) + 0.02 * accPitch;
  fusedRoll  = 0.98 * (fusedRoll + (gx / 131.0) * dt) + 0.02 * accRoll;

  // --- PID for pitch ---
  pitchError = 0 - fusedPitch; // target = 0 (level)
  pitchIntegral += pitchError * dt;
  float pitchDerivative = (pitchError - pitchPrevError) / dt;
  float pitchOutput = pitchKp * pitchError + pitchKi * pitchIntegral + pitchKd * pitchDerivative;
  pitchPrevError = pitchError;

  // --- PID for roll ---
  rollError = 0 - fusedRoll;
  rollIntegral += rollError * dt;
  float rollDerivative = (rollError - rollPrevError) / dt;
  float rollOutput = rollKp * rollError + rollKi * rollIntegral + rollKd * rollDerivative;
  rollPrevError = rollError;

  // Servo control (center at 90 degrees)
  int pitchServo = constrain(90 + pitchOutput, 0, 180);
  int rollServo = constrain(90 + rollOutput, 0, 180);

  servoPitch.write(pitchServo);
  servoRoll.write(rollServo);

  // Debug
  Serial.print("Pitch: "); Serial.print(fusedPitch);
  Serial.print("  Roll: "); Serial.println(fusedRoll);

  delay(10);  // Small delay for responsiveness (~100 Hz loop)
}

