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
    int data[3] = {0, 0, 0};
    void debugData();
    byte createCheckSum();
    const int dataSize = 3;
    
};

#endif
