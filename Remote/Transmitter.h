#ifndef Transmitter_h
#define Transmitter_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class Transmitter
{
  public:
    Transmitter();
    void transmitData();
    void setData(int capturedData[]);
    
  private:
    SoftwareSerial xBee;
    int data[4] = {0, 0, 0, 0};
    void debugData();
    byte createCheckSum();
    const int dataSize = 4;
    
};

#endif
