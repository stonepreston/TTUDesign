#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "MotorController.h"
#include <Servo.h>

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
  gateServo.attach(31);
}

void MotorController::drive() {

  // Left Motor
  if (leftSpeed <= (leftNeutral + neutralBump) && leftSpeed >= (leftNeutral - neutralBump)) {

    // Left stick is neutral
    leftMotor->run(RELEASE);
    
  } else if(leftSpeed < leftNeutral - neutralBump) {

    // Reverse
    // Map reverse values
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
    // Map reverse values
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

  if (leftSelect == 0 && rightSelect == 1) {

    // Left select is pressed, right select is not
    Serial.println("shooting");
    
    shootingServo.write(90);
    delay(90);
    shootingServo.write(0);
    
    
  }
}


void MotorController::toggleGate() {

  if (rightSelect == 0 && leftSelect == 1) {

    // Right select is pressed, left select is not
    
    if (gateClosed == true) {

      gateServo.write(0);
      gateClosed = false;
    } else {

      gateServo.write(90);
      gateClosed = true;
    }
    
    
  }
}


void MotorController::stopMotors() {

  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
  
}


void MotorController::calibrate() {

  if (leftSelect == 0 && rightSelect == 0) {

    // Both select buttons are pressed
    // reset neutral positions
    leftNeutral = leftSpeed;
    rightNeutral = rightSpeed;
    
  }

}

// Setters
void MotorController::setLeftSpeed(int leftSpeed) {

  this->leftSpeed = leftSpeed;
  
}

void MotorController::setRightSpeed(int rightSpeed) {

  this->rightSpeed = rightSpeed;
  
}

void MotorController::setLeftSelect(int leftSelect) {

  this->leftSelect = leftSelect;
  
}

void MotorController::setRightSelect(int rightSelect) {

  this->rightSelect = rightSelect;
  
}



