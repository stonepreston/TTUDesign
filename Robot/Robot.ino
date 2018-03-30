
#include "Arduino.h"
#include "Receiver.h"
#include "MotorController.h"

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

  // Check for timeout
  timeout();

  delay(10);
  
}

void timeout() {

  // See if we have 1 second between data
  if (receiver.getCurrentTime() > (receiver.getTimeOfLastGoodPacket() + 1000)) {
    // STop motors here
    Serial.println("Timeout");
    receiver.setTimeOfLastGoodPacket(receiver.getCurrentTime());
  }
}















