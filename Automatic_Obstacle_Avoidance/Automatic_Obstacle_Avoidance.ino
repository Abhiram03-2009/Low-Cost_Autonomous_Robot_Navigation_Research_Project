#include <Servo.h>

// ================== PINS ==================
#define PIN_SERVO           2

#define PIN_DIRECTION_LEFT  4
#define PIN_DIRECTION_RIGHT 3
#define PIN_MOTOR_PWM_LEFT  6
#define PIN_MOTOR_PWM_RIGHT 5

#define PIN_SONIC_TRIG      7
#define PIN_SONIC_ECHO      8

#define PIN_BATTERY         A0

// ================== MOTOR CONFIG ==================
// CHANGE THIS TO 1 IF ROBOT MOVES BACKWARDS
#define MOTOR_DIRECTION     0  

#define FWD_PWM     140   // MUST be >= 130 to move
#define TURN_PWM    170

// ================== OBSTACLE CONFIG ==================
#define OBSTACLE_DISTANCE       35
#define OBSTACLE_DISTANCE_LOW   15

#define MAX_DISTANCE    1000
#define SONIC_TIMEOUT   (MAX_DISTANCE * 60)
#define SOUND_VELOCITY  340

Servo servo;

// ================== SETUP ==================
void setup() {
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);

  pinMode(PIN_SONIC_TRIG, OUTPUT);
  pinMode(PIN_SONIC_ECHO, INPUT);

  servo.attach(PIN_SERVO);
  servo.write(90);

  // 🔥 HARD MOTOR TEST (CONFIRMS MOTORS WORK)
  motorRun(FWD_PWM, FWD_PWM);
  delay(1500);
}

// ================== LOOP ==================
void loop() {
  obstacleAvoid();
}

// ================== OBSTACLE AVOIDANCE ==================
void obstacleAvoid() {
  int front, left, right;

  // FRONT
  servo.write(90);
  delay(20);
  front = getSonar();

  // LEFT
  servo.write(150);
  delay(20);
  left = getSonar();

  // RIGHT
  servo.write(30);
  delay(20);
  right = getSonar();

  // ================= DECISION =================
  if (front < OBSTACLE_DISTANCE) {
    // BACK UP
    motorRun(-TURN_PWM, -TURN_PWM);
    delay(200);

    // TURN TOWARD CLEAR SIDE
    if (left > right) {
      motorRun(-TURN_PWM, TURN_PWM);
    } else {
      motorRun(TURN_PWM, -TURN_PWM);
    }
    delay(300);
  }
  else if (left < OBSTACLE_DISTANCE_LOW) {
    motorRun(TURN_PWM, FWD_PWM);
  }
  else if (right < OBSTACLE_DISTANCE_LOW) {
    motorRun(FWD_PWM, TURN_PWM);
  }
  else {
    // 🔥 ALWAYS MOVE FORWARD
    motorRun(FWD_PWM, FWD_PWM);
  }
}

// ================== SONAR ==================
int getSonar() {
  digitalWrite(PIN_SONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONIC_TRIG, LOW);

  unsigned long t = pulseIn(PIN_SONIC_ECHO, HIGH, SONIC_TIMEOUT);
  if (t == 0) return MAX_DISTANCE;

  return t * SOUND_VELOCITY / 2 / 10000;
}

// ================== MOTOR DRIVER ==================
void motorRun(int left, int right) {
  int dirL = left >= 0 ? (0 ^ MOTOR_DIRECTION) : (1 ^ MOTOR_DIRECTION);
  int dirR = right >= 0 ? (1 ^ MOTOR_DIRECTION) : (0 ^ MOTOR_DIRECTION);

  left = abs(left);
  right = abs(right);

  left = constrain(left, 0, 255);
  right = constrain(right, 0, 255);

  digitalWrite(PIN_DIRECTION_LEFT, dirL);
  digitalWrite(PIN_DIRECTION_RIGHT, dirR);
  analogWrite(PIN_MOTOR_PWM_LEFT, left);
  analogWrite(PIN_MOTOR_PWM_RIGHT, right);
}
