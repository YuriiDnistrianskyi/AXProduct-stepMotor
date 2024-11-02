#ifndef PINS_H
#define PINS_H

#include <AccelStepper.h>
#define HALFSTEP 8


const uint8_t pinButtonRight = 3;
const uint8_t pinButtonLeft = 2;

AccelStepper stepper1(AccelStepper::HALF4WIRE, 8, 10, 9, 11);

#endif // PINS_H
