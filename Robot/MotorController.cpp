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

  if (calibration == 1) {
    
    // reset neutral positions
    leftNeutral = leftSpeed;
    rightNeutral = rightSpeed;
    
  }

}

// Setters
void MotorController::setLeftSpeed(byte leftSpeed) {

  this->leftSpeed = int(leftSpeed);
  
}

void MotorController::setRightSpeed(byte rightSpeed) {

  this->rightSpeed = int(rightSpeed);
  
}

void MotorController::setSelect(byte select) {

  this->select = int(select);
  
}

void MotorController::setCalibration(byte calibration) {

  this->calibration = int(calibration);
  
}



