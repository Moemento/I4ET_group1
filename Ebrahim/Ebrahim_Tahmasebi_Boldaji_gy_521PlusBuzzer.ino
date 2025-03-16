
#include<Wire.h>  // this imports the Wire library, which allows the Arduino to communicate over I2C 

const int MPU_addr=0x68;  //This defines the I2C address of the MPU6050.
const int buzzer = 8;        // Buzzer connected to pin 8


int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //A data type that holds 16-bit integers (values from -32,768 to 32,767)

int minVal=265; //These are calibration values for the accelerometer (used to convert raw readings to angles).
int maxVal=402;

double x; double y; double z; //A floating-point number for more precise angle calculations

void setup()
    {
    Wire.begin();                     //Initializes the I2C bus for communication with the MPU6050 sensor.

    Wire.beginTransmission(MPU_addr);  
    Wire.write(0x6B);                //Begins communication with the sensor at I2C address 0x68
    Wire.write(0);                  //This sends 0 to the power management register, effectively waking up the sensor  
    Wire.endTransmission(true);     //Ends the communication and saves the settings
    Serial.begin(9600);             //Starts serial communication at 9600 baud rate (bits per second).
    pinMode(buzzer, OUTPUT);
    }
    
void loop(){ 
  
    Wire.beginTransmission(MPU_addr);     //Starts communication with the sensor at the address 0x68 (MPU)
    
    Wire.write(0x3B);                     //  
    Wire.endTransmission(false);          // Ends this part of the transmission without releasing the I2C bus (false keeps the connection active).
    Wire.requestFrom(MPU_addr,14,true);   // Requests 14 bytes of data from the MPU6050:
    AcX=Wire.read()<<8|Wire.read();       // Wire.read() reads one byte at a time.
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90); // map() scales the raw sensor values from minVal to maxVal into an angle range -90° to +90°
    int yAng = map(AcY,minVal,maxVal,-90,90); 
    int zAng = map(AcZ,minVal,maxVal,-90,90);
    
    x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);   // -yAng, -zAng, etc.: Negative signs flip directions to ensure correct orientation.
    y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);   //PI shifts the angle output to the correct quadrant.
    z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI); //RAD_TO_DEG converts radians to degrees & atan2() calculates the arc tangent
    
    Serial.print("AngleX= "); Serial.println(x); // Outputs the calculated X, Y, Z angles to the Serial Monitor
    
    Serial.print("AngleY= "); Serial.println(y);
    
    Serial.print("AngleZ= "); Serial.println(z);
    Serial.println("-----------------------------------------");
    

    // After this the sevomotor and buzzer code should be added 
    // It is like that whenever the angle of gyro is more than threshold value = 25 
    // the buzzer will active 
    // during the reading of angle the motor will rotate in the oposite direction of the equavalent angle to stablize the system
    if ((x < 25 && x > 0) || (x > 335 && x < 360)) {
      noTone(buzzer);
    } else {
      tone(buzzer, 1000);
    }
    delay(400);
}
