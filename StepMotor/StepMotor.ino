#include <Stepper.h>
#include "pins.h"

//TODO change mc!!
#define SERIAL_SPD 115200
#define MAX_SPD_LIM 2000
#define ACCEL_DEFAULT 1000
#define HALFSTEP 8

Stepper stepper1(2048, motorPin1, motorPin2, motorPin3, motorPin4);

volatile bool go = false;

//todo make in enum 
volatile bool right = false;
volatile bool left = false;


void goRight() { //IRAM_ATTR in esp
  // go = 2000;
  go = true;
  right = true;
}

void goLeft() {
  go = true;
  left = true;
}


void setup() {
  Serial.begin(SERIAL_SPD);
  stepper1.setSpeed(MAX_SPD_LIM); // in conf  // setMaxSpeed
  //stepper1.setAcceleration(ACCEL_DEFAULT);
  pinMode(pinButtonRight, INPUT_PULLUP);
  pinMode(pinButtonLeft, INPUT_PULLUP);

  //TODO add debounce for button!!!

  attachInterrupt(digitalPinToInterrupt(pinButtonRight), goRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinButtonLeft), goLeft, FALLING);
}

//TODO make another handler function for st motor
//TODO make header file for: button and its functions and for motor
//TODO lim position configuration add to eeprom/static memory

//todo watch gyver making project "dynamic ventilation setup" Ромі !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void loop() {
    if(go)
    {
      if(left){
        Serial.println("LEFT");
        stepper1.step(2048);
        left=false;
      }

      if(right){
        Serial.println("RIGHT");
        stepper1.step(-2048);
        right=false;
      }

      go=false;
    }

  //stepper1.run();
}
