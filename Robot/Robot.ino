
#include "Arduino.h"
#include "Receiver.h"

// Create Receiver object
Receiver receiver  = Receiver();

void setup()
{

  Serial.begin(9600);
  

}

void loop() {

  // Set current time on receiver
  receiver.setCurrentTime(millis());

  // Process data
  receiver.processData(); 

  timeout();

  
}

void timeout() {

  // See if we have 1 second between data
  if (receiver.getCurrentTime() > (receiver.getTimeOfLastGoodPacket() + 1000)) {
    // STop motors here
    Serial.println("Timeout");
    receiver.setTimeOfLastGoodPacket(receiver.getCurrentTime());
  }
}

//#include <SoftwareSerial.h>
//#include <Adafruit_MotorShield.h>
//
//// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
//
//// Select which 'port' M1, M2, M3 or M4. In this case, M1
//Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
//Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
//
//int leftNeutral = 244;
//int rightNeutral = 245;
//int neutralBump = 3;
//
//// rx = 13, tx = 3
//SoftwareSerial xBee(13, 3); // RX, TX
//
//// Network related variables
//// Flags
//bool usaFound = false;    
//bool uFound = false;    
//bool sFound = false;    
//bool aFound = false;   
//
//// Received data
//byte leftByte;
//byte rightByte;
//byte selectByte;
//byte calibrateByte;
//byte checkSumByte;
//
//byte badTx;
//word noTx = 0;
//
//// Used for timeouts
//unsigned long currentTime;
//unsigned long timeOfLastGoodPacket = 0;
//
//void setup() {
//
//  xBee.begin(9600);
//  Serial.begin(9600);
//
//  AFMS.begin();  // create with the default frequency 1.6KHz
//
//  // Set the speed to start, from 0 (off) to 255 (max speed)
//  leftMotor->setSpeed(150);
//  leftMotor->run(FORWARD);
//  // turn on motor
//  leftMotor->run(RELEASE);
//
//  // Set the speed to start, from 0 (off) to 255 (max speed)
//  rightMotor->setSpeed(150);
//  rightMotor->run(FORWARD);
//  // turn on motor
//  rightMotor->run(RELEASE);
//  
//}
//
//void loop() {
//
//  currentTime = millis();
//  processSerial(); 
//
//  // get speeds
//  int leftSpeed = int(leftByte); 
//  int rightSpeed = int(rightByte);
//
//  // Check for calibration
//  int calibrate = int(calibrateByte);
//
//  if (calibrateByte == 1) {
//
//    // reset neutral positions
//    leftNeutral = leftSpeed;
//    rightNeutral = rightSpeed;
//  }
//
//  // Left Motor
//  if (leftSpeed <= (leftNeutral + neutralBump) && leftSpeed >= (leftNeutral - neutralBump)) {
//
//    leftMotor->run(RELEASE);
//    
//  } else if(leftSpeed < leftNeutral + neutralBump) {
//
//    // Reverse
//    leftMotor->setSpeed(255); 
//    leftMotor->run(BACKWARD);
//    
//    
//    
//  } else {
//
//    // Forward
//    leftMotor->setSpeed(255); 
//    leftMotor->run(FORWARD);
//    
//  }
//
//  // Right Motor
//  if (rightSpeed <= (rightNeutral + neutralBump) && rightSpeed >= (rightNeutral - neutralBump)) {
//
//    rightMotor->run(RELEASE);
//    
//  } else if(rightSpeed <  rightNeutral + neutralBump) {
//
//    // Reverse
//    rightMotor->setSpeed(255); 
//    rightMotor->run(BACKWARD);
//
//    
//    
//  } else {
//
//    // Forward
//    rightMotor->setSpeed(255); 
//    rightMotor->run(FORWARD);
//    
//  }
//    
//  timeout();  
//  delay(10);
//  
//}
//
//void processSerial() {
//
//  unsigned char inputBufferTemp;
//  byte checkSumTest;
//
//  if (xBee.available() > 0 ) {
//
//    if (!uFound) {
//      
//      inputBufferTemp = xBee.read();
//      
//      if(inputBufferTemp == 0x55) { 
//        
//        uFound = true; 
//        
//      } 
//      else { 
//        
//        uFound = false; 
//        sFound = false; 
//        aFound = false; 
//        usaFound = false; 
//        
//      }
//    }
//
//    if (!sFound) {
//      
//      inputBufferTemp = xBee.read();
//      
//      if(inputBufferTemp == 0x53) { 
//        
//        sFound = true; 
//        
//      } 
//      else { 
//        
//        uFound = false; 
//        sFound = false; 
//        aFound = false; 
//        usaFound = false; 
//        
//      }
//    }
//
//    if (!aFound) {
//      
//      inputBufferTemp = xBee.read();
//      
//      if(inputBufferTemp == 0x41) { 
//        
//        aFound = true; 
//        usaFound = true;
//        
//      } 
//      else { 
//        
//        uFound = false; 
//        sFound = false; 
//        aFound = false; 
//        usaFound = false; 
//        
//      }
//    }
//
//    
//     if (usaFound && (xBee.available() )) {
//
//        Serial.println("Found Packet");
//        // The correct flags were found
//        // store bytes into the appropriate variables
//        leftByte = xBee.read();
//        rightByte = xBee.read();
//        selectByte = xBee.read();
//        calibrateByte = xBee.read();
//        checkSumByte = xBee.read();
//
//        // Clear flags
//        usaFound = false;
//        uFound = false; 
//        sFound = false; 
//        aFound = false;
//
//        // Calculate our checksum
//        checkSumTest = leftByte + rightByte + selectByte;
//
//        // Compare our calculated checksum to the expected
//        if (checkSumTest != checkSumByte) {  
//          
//          return; 
//          
//        }
//
//        // We found a good packet, so set current time
//        timeOfLastGoodPacket = currentTime;
//
//        
//
//        // Output data to serial
//        Serial.print("Left Byte: ");
//        Serial.println(leftByte);
//        Serial.print("Right Byte: ");
//        Serial.println(rightByte);
//        Serial.print("Select Byte: ");
//        Serial.println(selectByte);
//        Serial.print("Calibrate Byte: ");
//        Serial.println(calibrateByte);
//        
//     }
//    
//  }
//
//  
//}
//
//void timeout() {
//  if (currentTime > (timeOfLastGoodPacket + 1000)) {
//    // STop motors here
//    leftMotor->run(RELEASE);
//    rightMotor->run(RELEASE);
//    Serial.println("Timeout");
//    timeOfLastGoodPacket = currentTime;
//  }
//}













