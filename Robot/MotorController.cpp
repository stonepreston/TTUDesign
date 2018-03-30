#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "MotorController.h"

// Constructor
MotorController::MotorController() :  AFMS() {

  // Serial monitor is already started in Robot setup, no need to begin serial here

  // Initialize motors
  leftMotor = AFMS.getMotor(1);
  rightMotor = AFMS.getMotor(2);
  
  
}

void MotorController::drive(int leftSpeed, int rightSpeed) {
  
}


void MotorController::shoot() {

  
}

void MotorController::stopMotors() {

  
}


void MotorController::calibrate() {

  // reset neutral positions
  leftNeutral = leftSpeed;
  rightNeutral = rightSpeed;

}


