#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

uint8_t buttonRight = 2;
uint8_t buttonLeft = 4;

bool go = false;
bool right = false;
bool left = false;


void goRight() {
  go = true;
  right = true;
}

void goLeft() {
  go = true;
  left = true;
}

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(115200);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonRight), goRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonLeft), goLeft, FALLING);
}

void loop() {
  if (go) {
    if (right) {
      myStepper.step(stepsPerRevolution);
      right = false;
    } else {
      // step one revolution in the other direction:
      myStepper.step(-stepsPerRevolution);
      left = false;
    }
    go = false;
  }
}