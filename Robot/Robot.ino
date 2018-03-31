
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
  motorController.setSelect(receiver.getSelect());
  motorController.setCalibration(receiver.getCalibration());

  // Calibrate (if necessary)
  motorController.calibrate();

  motorController.drive();



  // Check for timeout
  timeout();

  // This affects performance, play around with it more
  // also check checksum stuff
  delay(70);


}

void timeout() {

  // See if we have 1 second between data
  if (receiver.getCurrentTime() > (receiver.getTimeOfLastGoodPacket() + 1000)) {

    Serial.println("timeout");
    // Stop motors here
    motorController.stopMotors();
    
    receiver.setTimeOfLastGoodPacket(receiver.getCurrentTime());
  }
}










