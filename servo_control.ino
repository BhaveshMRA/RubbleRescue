#include <ESP32Servo.h>

#define SERVO_X_PIN   18
#define SERVO_Y_PIN   19

#define SERVO_MIN      0
#define SERVO_NEUTRAL  60
#define SERVO_MAX      120
#define STEP           5

Servo servoX;
Servo servoY;

int angleX = SERVO_NEUTRAL;
int angleY = SERVO_NEUTRAL;

void setup() {
  Serial.begin(115200);
  servoX.attach(SERVO_X_PIN, 500, 2400);
  servoY.attach(SERVO_Y_PIN, 500, 2400);
  servoX.write(angleX);
  servoY.write(angleY);
  delay(500);
  Serial.println("Ready! W=up S=down A=left D=right C=center");
}

void loop() {
  if (Serial.available() > 0) {
    char key = Serial.read();
    switch (key) {
      case 'w': case 'W':
        angleY = constrain(angleY + STEP, SERVO_MIN, SERVO_MAX);
        Serial.printf("UP    → Servo Y: %d°\n", angleY);
        break;
      case 's': case 'S':
        angleY = constrain(angleY - STEP, SERVO_MIN, SERVO_MAX);
        Serial.printf("DOWN  → Servo Y: %d°\n", angleY);
        break;
      case 'a': case 'A':
        angleX = constrain(angleX - STEP, SERVO_MIN, SERVO_MAX);
        Serial.printf("LEFT  → Servo X: %d°\n", angleX);
        break;
      case 'd': case 'D':
        angleX = constrain(angleX + STEP, SERVO_MIN, SERVO_MAX);
        Serial.printf("RIGHT → Servo X: %d°\n", angleX);
        break;
      case 'c': case 'C':
        angleX = SERVO_NEUTRAL;
        angleY = SERVO_NEUTRAL;
        Serial.println("CENTER → both reset to 60°");
        break;
    }
    servoX.write(angleX);
    servoY.write(angleY);
  }
}

