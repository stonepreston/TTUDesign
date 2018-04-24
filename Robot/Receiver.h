#ifndef Receiver_h
#define Receiver_h

#include "Arduino.h"


class Receiver
{
  public:
    Receiver();
    void processData();
    int getLeftSpeed();
    int getRightSpeed();
    int getLeftTrigger();
    int getRightTrigger();
    void setCurrentTime(unsigned long timeInMillis);
    void setTimeOfLastGoodPacket(unsigned long timeInMillis);
    unsigned long getTimeOfLastGoodPacket();
    unsigned long getCurrentTime();
    
  private:
    
    // Data
    int processedData[4] = {0, 0, 1, 1};
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
