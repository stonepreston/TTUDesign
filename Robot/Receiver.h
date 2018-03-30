#ifndef Receiver_h
#define Receiver_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class Receiver
{
  public:
    Receiver();
    void processData();
    byte getLeftSpeed();
    byte getRightSpeed();
    byte getSelect();
    void setCurrentTime(unsigned long timeInMillis);
    void setTimeOfLastGoodPacket(unsigned long timeInMillis);
    unsigned long getTimeOfLastGoodPacket();
    unsigned long getCurrentTime();
    
  private:
    SoftwareSerial xBee;

    // Data
    byte processedData[4] = {0, 0, 0, 0};
    byte checkSumByte = 0;
    const int dataSize = 4;
    
    // Flags
    bool usaFound = false;    
    bool uFound = false;    
    bool sFound = false;    
    bool aFound = false;  

    // Used for timeouts
    unsigned long currentTime = 0;
    unsigned long timeOfLastGoodPacket = 0;
    
    void debugData();
    
    
    

    
};

#endif
