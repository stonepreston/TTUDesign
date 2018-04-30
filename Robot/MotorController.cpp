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
  leftMotor = AFMS.getMotor(2);
  rightMotor = AFMS.getMotor(1);
  shootingServo.attach(32);
  gateServo.attach(30);

  shootingServo.write(0);
  gateServo.write(90);
  
  
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

  // Check if only the shoot trigger is being pressed
  if (gateState == 1 && shootState == 0) {

    long int currentTime = millis();

    // Shoot only if long enough time has passed
    if (currentTime - lastShootTime > 500) {

      if (gateClosed == true) {

        gateServo.write(90);
        gateClosed = false;
        delay(200);
      }

      shootingServo.write(65);

      delay(300);
      shootingServo.write(0);
     
      lastShootTime = currentTime;
      Serial.println("shot fired");
      
    }
  }
  
}

void MotorController::toggleGate() {

  
  // Check if only the gate trigger is being pressed
  
  if (gateState == 0 && shootState == 1) {

    long int currentTime = millis();
    
    // Toggle only if long enough time has passed
    if (currentTime - lastToggleTime > 1000) {

      
      if (gateClosed == true) {

        
        gateServo.write(90);
        gateClosed = false;
        Serial.println("Opening Gate");
      
      } else {
  
        gateServo.write(0);
        gateClosed = true;
        Serial.println("Closing Gate");
      }
      
      lastToggleTime = currentTime;
      
    }

    
 }

  
}

void MotorController::stopMotors() {

  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
  
}


void MotorController::calibrate() {

  if (gateState == 0 && shootState == 0) {

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



