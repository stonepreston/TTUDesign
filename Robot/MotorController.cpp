#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "MotorController.h"

// Constructor
MotorController::MotorController() :  AFMS() {

  // Serial monitor is already started in Robot setup, no need to begin serial here

  // create with the default frequency 1.6KHz
  AFMS.begin();  

  // Initialize motors
  leftMotor = AFMS.getMotor(1);
  rightMotor = AFMS.getMotor(2);
  
  
}

void MotorController::drive(int leftSpeed, int rightSpeed) {

  // Left Motor
  if (leftSpeed <= (leftNeutral + neutralBump) && leftSpeed >= (leftNeutral - neutralBump)) {

    // Left stick is neutral
    leftMotor->run(RELEASE);
    
  } else if(leftSpeed < leftNeutral + neutralBump) {

    // Reverse
    leftMotor->setSpeed(255); 
    leftMotor->run(BACKWARD);
    
    
    
  } else {

    // Forward
    leftMotor->setSpeed(255); 
    leftMotor->run(FORWARD);
    
  }

  // Right Motor
  if (rightSpeed <= (rightNeutral + neutralBump) && rightSpeed >= (rightNeutral - neutralBump)) {

    // Right stick is neutral
    rightMotor->run(RELEASE);
    
  } else if(rightSpeed <  rightNeutral + neutralBump) {

    // Reverse
    rightMotor->setSpeed(255); 
    rightMotor->run(BACKWARD);

    
    
  } else {

    // Forward
    rightMotor->setSpeed(255); 
    rightMotor->run(FORWARD);
    
  }
  
}


void MotorController::shoot() {

  
}

void MotorController::stopMotors() {

  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
  
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



