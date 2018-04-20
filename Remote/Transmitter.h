#ifndef Transmitter_h
#define Transmitter_h

#include "Arduino.h"


class Transmitter
{
  public:
    Transmitter();
    void transmitData();
    void setData(int capturedData[]);
    
  private:
    
    int data[4] = {0, 0, 1, 0};
    void debugData();
    byte createCheckSum();
    const int dataSize = 4;
    
};

#endif
