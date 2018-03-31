#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Receiver.h"


// Constructor
Receiver::Receiver() :  xBee(13,3) {

  // Serial monitor is already started in main program, no need to begin serial here
  xBee.begin(9600);

  
  
}

void Receiver::processData() {

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

    
     if (usaFound && (xBee.available() )) {

        
        // The correct flags were found
        // store bytes into temp variables to calculate check sum
        byte tempLeft = xBee.read();
        byte tempRight = xBee.read();
        byte tempSelect = xBee.read();
        byte tempCalibrate = xBee.read();
        checkSumByte = xBee.read();

        // Calculate our checksum
        checkSumTest = tempLeft + tempRight + tempSelect;

        // Compare our calculated checksum to the expected
        if (checkSumTest != checkSumByte) {  

          Serial.println("CheckSum Failed!");
          return; 
          
        }

        processedData[0] = tempLeft;
        processedData[1] = tempRight;
        processedData[2] = tempSelect;
        processedData[3] = tempCalibrate;
 

        // Clear flags
        usaFound = false;
        uFound = false; 
        sFound = false; 
        aFound = false;


        // We found a good packet, so set current time
        timeOfLastGoodPacket = currentTime;

        

        // Output data to serial
        debugData();
        
     }
    
  }
  
}

void Receiver::debugData() {
  
  // Output data to serial
  Serial.print("Left Byte: ");
  Serial.println(processedData[0]);
  Serial.print("Right Byte: ");
  Serial.println(processedData[1]);
  Serial.print("Select Byte: ");
  Serial.println(processedData[2]);
  Serial.print("Calibrate Byte: ");
  Serial.println(processedData[3]);
  
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

byte Receiver::getCalibration() {

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

































