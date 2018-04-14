#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "MotorController.h"

// Constructor
MotorController::MotorController() : AFMS() {


}

void MotorController::initializeMotors() {

  // Initialize motors
  // Note: For some reason it didnt like AFMS.begin() being in the constructor, kinda strange
  AFMS.begin();
  leftMotor = AFMS.getMotor(1);
  rightMotor = AFMS.getMotor(2);
  shootingServo.attach(32);
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

  if (select == 0) {

    Serial.println("********shooting*********");
    shootingServo.write(120);
    delay(50);
    shootingServo.write(0);
    
  }
  
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



