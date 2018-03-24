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
    byte processedData[3] = {0, 0, 0};
    byte checkSumByte = 0;
    const int dataSize = 3;
    
    // Flags
    bool usaFound = false;    
    bool uFound = false;    
    bool sFound = false;    
    bool aFound = false;  

    // Used for timeouts
    unsigned long currentTime;
    unsigned long timeOfLastGoodPacket = 0;
    
    void debugData();
    
    
    

    
};

#endif
