#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "MotorControler.h"

// Constructor
MotorController::MotorController() :  AFMS() {

  // Serial monitor is already started in main program, no need to begin serial here

  // Initialize motors
  leftMotor = AFMS.getMotor(1);
  rightMotor = AFMS.getMotor(2);
  
  
}


