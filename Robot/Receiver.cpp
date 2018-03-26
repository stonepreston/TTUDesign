#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Receiver.h"


// Constructor
Receiver::Receiver() :  xBee(13,3) {

  Serial.begin(9600);
  
  
}

void Receiver::processData() {

  // TODO: Move this begin into constructor and see if that helps receiving rate
  // TODO: Use individual member variables instead of array. Array accessing might be causing the slow down.
  xBee.begin(9600);
  unsigned char inputBufferTemp;
  byte checkSumTest;

  

  if (xBee.available() > 0 ) {
  

    if (!uFound) {
      
      inputBufferTemp = xBee.read();
      
      if(inputBufferTemp == 0x55) { 
        
        uFound = true; 
        
      } 
      else { 
        
        uFound = false; 
        sFound = false; 
        aFound = false; 
        usaFound = false; 
        
      }
    }

    if (!sFound) {
      
      inputBufferTemp = xBee.read();
      
      if(inputBufferTemp == 0x53) { 
        
        sFound = true; 
        
      } 
      else { 
        
        uFound = false; 
        sFound = false; 
        aFound = false; 
        usaFound = false; 
        
      }
    }

    if (!aFound) {
      
      inputBufferTemp = xBee.read();
      
      if(inputBufferTemp == 0x41) { 
        
        aFound = true; 
        usaFound = true;
        
      } 
      else { 
        
        uFound = false; 
        sFound = false; 
        aFound = false; 
        usaFound = false; 
        
      }
    }

    
     if (usaFound && (xBee.available())) {

        Serial.println("Found Packet:");

        // The correct flags were found
        // store bytes into the appropriate variables
        processedData[0] = xBee.read();
        processedData[1] = xBee.read();
        processedData[2] = xBee.read();
        processedData[3] = xBee.read();
        checkSumByte = xBee.read();

        // Clear flags
        usaFound = false;
        uFound = false; 
        sFound = false; 
        aFound = false;
        

        // Calculate our checksum
        checkSumTest = processedData[0] + processedData[1] + processedData[2];

        // Compare our calculated checksum to the expected
        if (checkSumTest != checkSumByte) {  

          Serial.println("Checksum failed");
          return; 
          
        }

       

        // We found a good packet, so set current time
        timeOfLastGoodPacket = currentTime;

        

        // Output data to serial
        Serial.print("Left Byte: ");
        Serial.println(processedData[0]);
        Serial.print("Right Byte: ");
        Serial.println(processedData[1]);
        Serial.print("Select Byte: ");
        Serial.println(processedData[2]);
        
     }
    
  }
  
}

byte Receiver::getLeftSpeed() {

  return processedData[0];
  
}

byte Receiver::getRightSpeed() {

  return processedData[1];

  
}

byte Receiver::getSelect() {

  return processedData[2];
  
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

































