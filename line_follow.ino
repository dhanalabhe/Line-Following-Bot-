#include <SoftwareSerial.h>

// LSA08 Serial communication setup
SoftwareSerial LSA08(0, 1); // RX, TX (connect TX of Arduino to RX of LSA08 and vice versa)

// Define motor control pins for L298N
#define ENA 11  // PWM pin for motor A speed
#define IN1 13  // Direction pin for motor A
#define IN2 12  // Direction pin for motor A
#define ENB 10  // PWM pin for motor B speed
#define IN3 9   // Direction pin for motor B
#define IN4 8   // Direction pin for motor B

// Constants for PID control
const int baseSpeed = 200;  // Base speed for motors
const int maxSpeed = 255;   // Maximum allowable motor speed
const float Kp = 7.0;       // Proportional gain
const float Ki = 0.0;       // Integral gain (often 0 for line-following)
const float Kd = 13.0;      // Derivative gain

// PID variables
int lastError = 0;
int integral = 0;

void setup() {
  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Start serial communication with LSA08 at the baud rate of 57600
  LSA08.begin(57600);
}

void loop() {
  int position = readLinePosition(); // Read position from LSA08 sensor
  int error = 3500 - position; // Calculate error based on desired position
  integral += error; // Accumulate integral
  int derivative = error - lastError; // Calculate derivative
  int correction = Kp * error + Ki * integral + Kd * derivative; // PID correction
  lastError = error;

  // Calculate motor speeds based on correction
  int leftMotorSpeed = baseSpeed - correction;
  int rightMotorSpeed = baseSpeed + correction;

  // Limit motor speeds
  leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);

  // Apply the calculated speeds to the motors
  setMotorSpeed(leftMotorSpeed, rightMotorSpeed);
}

// Read line position from LSA08 sensor via UART
int readLinePosition() {
  int position = 0;
  if (LSA08.available() > 0) {
    position = LSA08.parseInt();  // Reads position as an integer from LSA08
  }
  return position;
}

// Set motor speeds and directions
void setMotorSpeed(int leftSpeed, int rightSpeed) {
  // Set direction and speed for left motor (Motor A)
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    leftSpeed = -leftSpeed; // Convert to positive for PWM
  }
  analogWrite(ENA, leftSpeed); // Apply speed for left motor

  // Set direction and speed for right motor (Motor B)
  if (rightSpeed > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    rightSpeed = -rightSpeed; // Convert to positive for PWM
  }
  analogWrite(ENB, rightSpeed); // Apply speed for right motor
}
