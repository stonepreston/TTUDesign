
#include <SoftwareSerial.h>

//// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
//// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial xBee(2, 3); // RX, TX

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
      
      if(inputBufferTemp == 0x55) { 
        
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

    
     if (usaFound && (xBee.available()  > 3 )) {

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

        Serial.println("Found Packet:");

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












//#include <AFMotor.h>
//
//// We'll use SoftwareSerial to communicate with the XBee:
//#include <SoftwareSerial.h>
//// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
//// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
//SoftwareSerial XBee(2, 3); // RX, TX
//
//AF_DCMotor motor(1,MOTOR12_8KHZ);
//
//void setup()
//{
//  // Set up both ports at 9600 baud. This value is most important
//  // for the XBee. Make sure the baud rate matches the config
//  // setting of your XBee.
//  XBee.begin(9600);
//  Serial.begin(9600);
//
//  
//  // turn on motor #4
//  motor.setSpeed(255);
//  motor.run(RELEASE);
//  
//}
//
//void loop()
//{
//  if (Serial.available())
//  { // If data comes in from serial monitor
//    XBee.write(Serial.read());
//  }
//  if (XBee.available())
//  { // If data comes in from XBee
//
//    int xbeeData = XBee.parseInt();
//    if (xbeeData > 1023) {
//      xbeeData = 1023;
//    }
//
//    if (xbeeData < 0) {
//      xbeeData = 0;
//    }
//
//    int speed = map(xbeeData, 0, 1023, 0, 255);
//    Serial.print("speed: ");
//    Serial.println(speed);
//
//    // Stop the motor if the stick is neutral
//    if (speed <= 127 && speed >= 122) {
//
//      motor.run(RELEASE); 
//        
//    } else {
//
//     
//      if (speed > 127) {
//        
//        motor.setSpeed(speed);
//        Serial.print("forward speed: ");
//        Serial.println(speed);
//        motor.run(FORWARD);  
//        
//      }
//
//      if (speed < 122) {
//
//        // remap for reverse speed
//        int reverseSpeed = map(speed, 0, 255, 255, 0);
//        Serial.println("reverse speed: ");
//        Serial.print(reverseSpeed);
//        motor.setSpeed(reverseSpeed);
//        motor.run(BACKWARD);
//
//      }
//       
//      
//    }
//       
//    
//  }
//
//  
//}

