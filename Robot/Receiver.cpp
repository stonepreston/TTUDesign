#include "Arduino.h"
#include "Receiver.h"


// Constructor
Receiver::Receiver()  {

  // Serial monitor is already started in main program, no need to begin serial here
  

  
  
}

void Receiver::processData() {

  unsigned char inputBufferTemp;
  byte chksumTest;

  Serial1.begin(9600);

  // Wait for xbee
  if (Serial1.available() > 0) {

    if (!uFound) {
      inputBufferTemp = Serial1.read();
      if(inputBufferTemp == 0x55) { uFound = true; } 
      else { uFound = false; sFound = false; aFound = false; usaFound = false; }
    }
    
    if (!sFound) {
      inputBufferTemp = Serial1.read();
      if(inputBufferTemp == 0x53) { sFound = true; } 
      else {  uFound = false; sFound = false; aFound = false; usaFound = false; }
    }
    
    if (!aFound) {
      inputBufferTemp = Serial1.read();
      if(inputBufferTemp == 0x41) { aFound = true; usaFound = true;} 
      else { uFound = false; sFound = false; aFound = false; usaFound = false; }
    }

    if (usaFound && (Serial1.available()  > 4 )) {
      
      // store bytes into the appropriate variables
      
      processedData[0] = Serial1.read();
      processedData[1] = Serial1.read();
      processedData[2] = Serial1.read();
      processedData[3] = Serial1.read();
      checkSumByte = Serial1.read();
      
      // Clear flags
      usaFound = false;
      uFound = false; 
      sFound = false; 
      aFound = false;

      
      // Calculate our checksum
      chksumTest = byte(processedData[0] + processedData[1] + processedData[2] + processedData[3]);
      
      // Compare our calculated checksum to the expected
      if (chksumTest != checkSumByte) {  

        Serial.println("Checksum failed!");
        return; 
      }

      // debugData(); 
      
      // We found a good packet, so set current time
      timeOfLastGoodPacket = currentTime;

      
  
    } 
  } 


  
}

void Receiver::debugData() {
  
  // Output data to serial
  Serial.print("Left Speed: ");
  Serial.println(processedData[0]);
  Serial.print("Right Speed: ");
  Serial.println(processedData[1]);
  Serial.print("Left Trigger: ");
  Serial.println(processedData[2]);
  Serial.print("Right Trigger: ");
  Serial.println(processedData[3]);
  Serial.print("CheckSumByte: ");
  Serial.println(checkSumByte);

  
}

int Receiver::getLeftSpeed() {

  return processedData[0];
  
}

int Receiver::getRightSpeed() {

  return processedData[1];

  
}

int Receiver::getLeftTrigger() {

  return processedData[2];
  
}

int Receiver::getRightTrigger() {

  return processedData[3];
  
}

void Receiver::setCurrentTime(unsigned long timeInMillis) {

  currentTime = timeInMillis;
}

void Receiver::setTimeOfLastGoodPacket(unsigned long timeInMillis) {

  timeOfLastGoodPacket = timeInMillis;
}

unsigned long Receiver::getTimeOfLastGoodPacket() {

  return timeOfLastGoodPacket;
}


unsigned long Receiver::getCurrentTime() {

  return currentTime;
}

































