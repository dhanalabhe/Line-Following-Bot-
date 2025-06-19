# 🚗 Line Follower Robot using Arduino and L298N Motor Driver

This project is a simple **line-following robot** using an Arduino, L298N motor driver, and a single analog line sensor (LSA08). The robot uses error-based logic to adjust its motor speeds and follow a line accurately with smooth turns.

## 🛠 Components Used

- Arduino Uno/Nano
- L298N Motor Driver Module
- 2 DC Motors with wheels
- LSA08 Analog Line Sensor (or equivalent analog sensor)
- Power supply (Battery)
- Chassis and wheels
- Jumper wires

## 📋 Features

- Proportional line-following behavior based on sensor error
- Smooth handling of gentle, medium, and sharp turns
- Serial monitor feedback for debugging
- Adjustable thresholds for tuning performance

## 🧠 Working Principle

The robot continuously reads analog values from a line sensor and compares them to a set reference point (`setPoint`). Based on the difference (`error`), it adjusts the left and right motor speeds accordingly.

- If the robot drifts **right**, left motor speed is increased and right is decreased.
- If the robot drifts **left**, right motor speed is increased and left is decreased.
- If the robot is centered, both motors run at base speed.

## 🧾 Code Overview

```cpp
#define SENSOR_PIN A0 // Reads from analog sensor
int setPoint = 680;   // Center value for tracking line
```

Motor speed is adjusted depending on the `error`:

```cpp
if (error > largeError) {
  // Sharp Right Turn
} else if (error < -largeError) {
  // Sharp Left Turn
} else {
  // Gentle turns or straight
}
```

The `driveMotor()` function handles motor direction and speed using PWM signals:

```cpp
void driveMotor(int in1, int in2, int en, int speed)
```

## 🔌 Pin Configuration

| Component      | Arduino Pin |
|----------------|-------------|
| Left Motor EN  | 10          |
| Left Motor IN1 | 5           |
| Left Motor IN2 | 6           |
| Right Motor EN | 11          |
| Right Motor IN1| 8           |
| Right Motor IN2| 7           |
| Line Sensor    | A0          |

## ⚙️ Adjustable Parameters

You can tune the following values to optimize performance:

- `setPoint` — Center value for the sensor
- `baseSpeed`, `adjustSpeed`, `sharpadjust` — Speeds for turns and straight motion
- `smallError`, `mediumError`, `largeError` — Error thresholds for different turning behavior

## 📈 Sample Serial Output

```
Sensor: 672 Error: -8 Left Speed: 105 Right Speed: 105
Sensor: 790 Error: 110 Left Speed: 205 Right Speed: 105
```

Use the serial monitor for calibration and tuning.

## 🔄 Future Improvements

- Add PID control for more accurate and smooth line following
- Use multiple digital sensors instead of a single analog sensor
- Add obstacle detection with ultrasonic sensor

## 🧪 How to Run

1. Wire the components as described above.
2. Upload the code to the Arduino board.
3. Place the robot on a black line over a white surface.
4. Power the system and watch the robot follow the line!

## 📄 License

This project is licensed under the MIT License.

---

Happy building! 😊
