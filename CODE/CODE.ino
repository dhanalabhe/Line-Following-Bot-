// Pin Definitions
#define MOTOR_LEFT_EN 10  
#define MOTOR_LEFT_IN1 5   
#define MOTOR_LEFT_IN2 6  
#define MOTOR_RIGHT_EN 11  
#define MOTOR_RIGHT_IN1 8 
#define MOTOR_RIGHT_IN2 7
#define SENSOR_PIN A0      

// Setpoints for error thresholds
int setPoint = 680;       // Middle value for the sensor
int smallError = 75;      // Threshold for small deviation
int mediumError = 100;    // Threshold for medium deviation
int largeError = 270;    
int exterror =500;// Threshold for large deviation

// Motor speed settings
int baseSpeed = 105; 
int adjustSpeed =100;
int sharpadjust=150; 
int maxSpeed = 255;  

void setup() {
  pinMode(MOTOR_LEFT_EN, OUTPUT);
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_RIGHT_EN, OUTPUT);
  pinMode(MOTOR_RIGHT_IN1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN2, OUTPUT);

  Serial.begin(9600); 

void loop() {
  
  int sensorValue = analogRead(SENSOR_PIN);
  Serial.print(sensorValue);

  
  int error = sensorValue - setPoint;
  Serial.print(error);

  
  int leftSpeed = baseSpeed;
  int rightSpeed = baseSpeed;

  if (error > largeError) {
    
    leftSpeed = baseSpeed -15+ adjustSpeed * 2;
    rightSpeed = baseSpeed +15- adjustSpeed * 2;
  } else if (error > mediumError) {
    
    leftSpeed = baseSpeed + adjustSpeed;
    rightSpeed = baseSpeed;
  } else if (error > smallError) {
    
    leftSpeed = baseSpeed + adjustSpeed / 2;
    rightSpeed = baseSpeed - adjustSpeed / 2;
  }
  else if(error < exterror){
    leftSpeed = baseSpeed - sharpadjust * 3;
    rightSpeed = baseSpeed+ sharpadjust * 3;
    
  } else if (error < -largeError) {
    
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed + sharpadjust* 2;
  } else if (error < -mediumError) {
   
    leftSpeed = baseSpeed - sharpadjust;
    rightSpeed = baseSpeed +sharpadjust;
  } else if (error < -smallError) {
    
    leftSpeed = baseSpeed - adjustSpeed / 2;
    rightSpeed = baseSpeed + adjustSpeed / 2;
  } else {
    
    leftSpeed = baseSpeed+20;
    rightSpeed = baseSpeed+20;
  }

  // Drive the motors
  driveMotor(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_EN, leftSpeed);
  driveMotor(MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_EN, rightSpeed);

  // Debugging
  Serial.print("Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" Error: ");
  Serial.print(error);
  Serial.print(" Left Speed: ");
  Serial.print(leftSpeed);
  Serial.print(" Right Speed: ");
  Serial.println(rightSpeed);

  delay(10); 
}

void driveMotor(int in1, int in2, int en, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    speed = -speed; // Convert negative speed to positive
  }
  analogWrite(en, constrain(speed, 0, maxSpeed));
}
