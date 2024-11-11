#include <AccelStepper.h>
#include "pins.h"

//TODO change mc!!
#define SERIAL_SPD 115200
#define MAX_SPD_LIM 2000
#define ACCEL_DEFAULT 1000

volatile int go = 0;
// uint16_t
// uint32_t

//todo make in enum 
volatile bool right = false;
volatile bool left = false;


void goRight() { //IRAM_ATTR in esp
  // go = 2000;
  go += 100;
  right = true;
}

void goLeft() {
  go -= 100;
  left = true;
}


void setup() {
  Serial.begin(SERIAL_SPD);
  stepper1.setMaxSpeed(MAX_SPD_LIM); // in conf
  stepper1.setAcceleration(ACCEL_DEFAULT);
  pinMode(pinButtonRight, INPUT_PULLUP);
  pinMode(pinButtonLeft, INPUT_PULLUP);

  //TODO add debounce for button!!!

  attachInterrupt(digitalPinToInterrupt(pinButtonRight), goRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinButtonLeft), goLeft, FALLING);
}

//TODO make another handler function for st motor
//TODO make header file for: button and its functions and for motor
//TODO lim position configuration add to eeprom/static memory

//todo watch gyver making project "dynamic ventilation setup"

void loop() {
    if(go)
    {
      if(left){
        Serial.println("LEFT");
        stepper1.move(go);
        left=false;
      }

      if(right){
        Serial.println("RIGHT");
        stepper1.move(go);
        right=false;
      }

      go=0;
    }
  

  // if (go != 0) {
    // stepper1.moveTo(go);
    // go = 0;
  // }

  stepper1.run();
}
