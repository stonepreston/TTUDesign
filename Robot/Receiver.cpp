#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Receiver.h"


// Constructor
Receiver::Receiver() :  xBee(13,3) {

  // Serial monitor is already started in main program, no need to begin serial here
  

  
  
}

void Receiver::processData() {

  unsigned char inputBufferTemp;
  byte checkSumTest;

  xBee.begin(9600);

  if (xBee.available() > 0) {
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

          if (uFound == true && sFound == true && aFound == true) {

            usaFound = true;
            
          } else {

            usaFound = false;
            
          }

        
          
          
        } 
        else { 
          
          uFound = false; 
          sFound = false; 
          aFound = false; 
          usaFound = false; 
          
        }
      }

    
    
     if (usaFound && (xBee.available() > 4 )) {


        Serial.println("Found Packet");
        // The correct flags were found
        // store bytes into temp variables to calculate check sum
        byte tempLeft = xBee.read();
        byte tempRight = xBee.read();
        byte tempSelect = xBee.read();
        byte tempCalibrate = xBee.read();
        byte tempCheckSum = xBee.read();

        // Clear flags
        usaFound = false;
        uFound = false; 
        sFound = false; 
        aFound = false;

        // Calculate our checksum
        checkSumTest = tempLeft + tempRight + tempSelect + tempCalibrate;

        // Compare our calculated checksum to the expected
        if (checkSumTest != tempCheckSum) {  

          Serial.println("CheckSum Failed!");
          Serial.print("Transmitter CheckSum: ");
          Serial.println(tempCheckSum);
          Serial.print("Receiver Calculated CheckSum: ");
          Serial.println(checkSumTest);

  
          return; 
          
        }

        processedData[0] = tempLeft;
        processedData[1] = tempRight;
        processedData[2] = tempSelect;
        processedData[3] = tempCalibrate;
        checkSumByte = tempCheckSum;


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
  Serial.print("CheckSumByte: ");
  Serial.println(checkSumByte);

  
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

































