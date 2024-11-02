#include <AccelStepper.h>
#include "pins.h"

volatile int go = 0;

void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(2000); // in conf
  stepper1.setAcceleration(1000);
  pinMode(pinButtonRight, INPUT_PULLUP);
  pinMode(pinButtonLeft, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinButtonRight), goRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinButtonLeft), goLeft, FALLING);
}

void loop() {
  if (go != 0) {
    stepper1.moveTo(go);
    go = 0;
  }

  stepper1.run();
}

void goRight() {
  go = 1000;
}

void goLeft() {
  go = -1000;
}
