
#include "Arduino.h"
#include "Receiver.h"
#include "MotorController.h"

// Create Receiver object
Receiver receiver  = Receiver();

// Create MotorController object
MotorController motorController = MotorController();

void setup()
{

  Serial.begin(9600);
  
  motorController.initializeMotors();
  
}

void loop() {

  // Set current time on receiver
  receiver.setCurrentTime(millis());

  // Process data
  receiver.processData(); 

  // Set motor controller variables
  motorController.setLeftSpeed(receiver.getLeftSpeed());
  motorController.setRightSpeed(receiver.getRightSpeed());
  motorController.setLeftSelect(receiver.getLeftSelect());
  motorController.setRightSelect(receiver.getRightSelect());

  motorController.calibrate();

  motorController.drive();
  
  motorController.shoot();
  
  motorController.toggleGate();

  // Check for timeout
  timeout();

}

void timeout() {

  // See if we have 1 second between data
  if (receiver.getCurrentTime() > (receiver.getTimeOfLastGoodPacket() + 1000)) {

    Serial.println("timeout");
 
    motorController.stopMotors();
    
    receiver.setTimeOfLastGoodPacket(receiver.getCurrentTime());
  }
}










