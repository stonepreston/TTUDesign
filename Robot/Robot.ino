
//#include "Arduino.h"
//#include "Receiver.h"
//
//// Create Receiver object
//Receiver receiver  = Receiver();
//
//void setup()
//{
//
//  Serial.begin(9600);
//  
//
//}
//
//void loop() {
//
//  // Set current time on receiver
//  receiver.setCurrentTime(millis());
//
//  // Process data
//  receiver.processData(); 
//
//  //timeout();
//
//  
//}
//
//void timeout() {
//
//  // See if we have 1 second between data
//  if (receiver.getCurrentTime() > (receiver.getTimeOfLastGoodPacket() + 1000)) {
//    // STop motors here
//    Serial.println("Timeout");
//    receiver.setTimeOfLastGoodPacket(receiver.getCurrentTime());
//  }
//}

#include <SoftwareSerial.h>
#include <Adafruit_MotorShield.h>


// rx = 13, tx = 3
SoftwareSerial xBee(13, 3); // RX, TX

// Network related variables
// Flags
bool usaFound = false;    
bool uFound = false;    
bool sFound = false;    
bool aFound = false;   

// Received data
byte leftByte;
byte rightByte;
byte selectByte;
byte checkSumByte;

byte badTx;
word noTx = 0;

// Used for timeouts
unsigned long currentTime;
unsigned long timeOfLastGoodPacket = 0;

void setup() {

  xBee.begin(9600);
  Serial.begin(9600);
  
}

void loop() {

  currentTime = millis();
  processSerial();  
 timeout();  
  delay(10);
  
}

void processSerial() {

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

        Serial.println("Found Packet");
        // The correct flags were found
        // store bytes into the appropriate variables
        leftByte = xBee.read();
        rightByte = xBee.read();
        selectByte = xBee.read();
        checkSumByte = xBee.read();

        // Clear flags
        usaFound = false;
        uFound = false; 
        sFound = false; 
        aFound = false;

        // Calculate our checksum
        checkSumTest = leftByte + rightByte + selectByte;

        // Compare our calculated checksum to the expected
        if (checkSumTest != checkSumByte) {  
          
          return; 
          
        }

        // We found a good packet, so set current time
        timeOfLastGoodPacket = currentTime;

        

        // Output data to serial
        Serial.print("Left Byte: ");
        Serial.println(leftByte);
        Serial.print("Right Byte: ");
        Serial.println(rightByte);
        Serial.print("Select Byte: ");
        Serial.println(selectByte);
        
     }
    
  }

  
}

void timeout() {
  if (currentTime > (timeOfLastGoodPacket + 1000)) {
    // STop motors here
    Serial.println("Timeout");
    timeOfLastGoodPacket = currentTime;
  }
}













