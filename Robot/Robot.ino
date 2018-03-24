
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

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

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

  AFMS.begin();  // create with the default frequency 1.6KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(150);
  motor1->run(FORWARD);
  // turn on motor
  motor1->run(RELEASE);

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor2->setSpeed(150);
  motor2->run(FORWARD);
  // turn on motor
  motor2->run(RELEASE);
  
}

void loop() {

  currentTime = millis();
  processSerial(); 
  int leftSpeed = int(leftByte); 
  int rightSpeed = int(rightByte);

  motor1->setSpeed(leftSpeed); 
  motor1->run(FORWARD);
  motor2->setSpeed(rightSpeed); 
  motor2->run(FORWARD);
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
    motor1->run(RELEASE);
    motor2->run(RELEASE);
    Serial.println("Timeout");
    timeOfLastGoodPacket = currentTime;
  }
}













