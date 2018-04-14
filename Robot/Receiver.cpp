#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Receiver.h"


// Constructor
Receiver::Receiver() :  xBee(13,3) {

}

void Receiver::processData() {

  unsigned char inputBufferTemp;
  byte chksumTest;

  xBee.begin(9600);

  // Wait for xbee
  if (xBee.available() > 0) {

    if (!uFound) {
      inputBufferTemp = xBee.read();
      if(inputBufferTemp == 0x55) { uFound = true; } 
      else { uFound = false; sFound = false; aFound = false; usaFound = false; }
    }
    
    if (!sFound) {
      inputBufferTemp = xBee.read();
      if(inputBufferTemp == 0x53) { sFound = true; } 
      else {  uFound = false; sFound = false; aFound = false; usaFound = false; }
    }
    
    if (!aFound) {
      inputBufferTemp = xBee.read();
      if(inputBufferTemp == 0x41) { aFound = true; usaFound = true;} 
      else { uFound = false; sFound = false; aFound = false; usaFound = false; }
    }

    if (usaFound && (xBee.available()  > 3 )) {
      
      // store bytes into the appropriate variables
      
      processedData[0] = xBee.read();
      processedData[1] = xBee.read();
      processedData[2] = xBee.read();
      processedData[3] = xBee.read();
      checkSum = xBee.read();
      
      // Clear flags
      usaFound = false;
      uFound = false; 
      sFound = false; 
      aFound = false;
      
      // Calculate our checksum
      chksumTest = processedData[0] + processedData[1] + processedData[2] + processedData[3];
      
      // Compare our calculated checksum to the expected
      if (chksumTest != checkSum) {  

        Serial.println("Checksum failed!");
        return; 
      }
      
      // We found a good packet, so set current time
      timeOfLastGoodPacket = currentTime;

      //debugData();
  
    } 
  } 
  
}

void Receiver::debugData() {
  
  // Output data to serial
  Serial.print("Left: ");
  Serial.println(processedData[0]);
  Serial.print("Right: ");
  Serial.println(processedData[1]);
  Serial.print("Select: ");
  Serial.println(processedData[2]);
  Serial.print("Calibrate: ");
  Serial.println(processedData[3]);
  Serial.print("CheckSum: ");
  Serial.println(checkSum);

  
}

int Receiver::getLeftSpeed() {

  return processedData[0];
  
}

int Receiver::getRightSpeed() {

  return processedData[1];

  
}

int Receiver::getSelect() {

  return processedData[2];
  
}

int Receiver::getCalibration() {

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

































