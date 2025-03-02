#include <Stepper.h>

#define LED_PIN 2

#define STEPS_PER_REV 2048  

// Define motor 1 pins (Left motor)
#define M1_IN1 14  // D14
#define M1_IN2 27  // D27
#define M1_IN3 26  // D26
#define M1_IN4 25  // D25

// Define motor 2 pins (Right motor) with D23 instead of D22
#define M2_IN1 18  // D18
#define M2_IN2 19  // D19
#define M2_IN3 21  // D21
#define M2_IN4 23  // D23 (Updated from D22)

Stepper stepper1(STEPS_PER_REV, M1_IN1, M1_IN3, M1_IN2, M1_IN4);
Stepper stepper2(STEPS_PER_REV, M2_IN1, M2_IN3, M2_IN2, M2_IN4);

void setup() {
  stepper1.setSpeed(20);
  stepper2.setSpeed(20);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  stepper1.step(STEPS_PER_REV);
  stepper2.step(STEPS_PER_REV);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  stepper1.step(-STEPS_PER_REV);
  stepper2.step(-STEPS_PER_REV);
  delay(1000);
}
