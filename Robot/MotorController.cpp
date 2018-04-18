#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "MotorController.h"

// Constructor
MotorController::MotorController() : AFMS() {

  // Serial monitor is already started in Robot setup, no need to begin serial here

  
  
  
  
}

void MotorController::initializeMotors() {

  // Initialize motors
  // Note: For some reason it didnt like AFMS.begin() being in the constructor, kinda strange
  AFMS.begin();
  leftMotor = AFMS.getMotor(1);
  rightMotor = AFMS.getMotor(2);
}

void MotorController::drive() {

  // Left Motor
  if (leftSpeed <= (leftNeutral + neutralBump) && leftSpeed >= (leftNeutral - neutralBump)) {

    // Left stick is neutral
    leftMotor->run(RELEASE);
    
  } else if(leftSpeed < leftNeutral - neutralBump) {

    // Reverse
    int leftReverseSpeed = map(leftSpeed, 0, 255, 255, 0);
    leftMotor->setSpeed(leftReverseSpeed); 
    leftMotor->run(BACKWARD);
    
    
    
  } else {

    // Forward
    leftMotor->setSpeed(leftSpeed); 
    leftMotor->run(FORWARD);
    
    
  }

  // Right
  if (rightSpeed <= (rightNeutral + neutralBump) && rightSpeed >= (rightNeutral - neutralBump)) {

    // Right stick is neutral
    rightMotor->run(RELEASE);
    
  } else if(rightSpeed < rightNeutral - neutralBump) {

    // Reverse
    int rightReverseSpeed = map(rightSpeed, 0, 255, 255, 0);
    rightMotor->setSpeed(rightReverseSpeed); 
    rightMotor->run(BACKWARD);
   
    
  } else {

    // Forward
    rightMotor->setSpeed(rightSpeed); 
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

  if (gateState == 1 && shootState == 0) {

    // Both left and right triggers are pressed
    
    // reset neutral positions
    leftNeutral = leftSpeed;
    rightNeutral = rightSpeed;
    Serial.println("Calibrating");
  }

}

// Setters
void MotorController::setLeftSpeed(byte leftSpeed) {

  this->leftSpeed = int(leftSpeed);
  
}

void MotorController::setRightSpeed(byte rightSpeed) {

  this->rightSpeed = int(rightSpeed);
  
}

void MotorController::setShoot(byte shoot) {

  this->shootState = int(shoot);

}

void MotorController::setGate(byte gate) {

  this->gateState = int(gate);
  
}



