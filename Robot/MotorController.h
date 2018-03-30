#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include <Adafruit_MotorShield.h>

class MotorController
{
  public:

    // Constructor
    MotorController();

    void drive(int leftSpeed, int rightSpeed);
    void shoot();
    
    
  private:
  
    Adafruit_MotorShield AFMS

    // Neutral stick positioning
    int leftNeutral = 244; // First guess without calibration
    int rightNeutral = 245; // First guess without calibration
    int neutralBump = 3; 

    // Speed Related
    int leftSpeed = 0;
    int rightSpeed = 0;

    // Calibration
    // 0 = off, 1 = on (pull down resistor)
    int calibrate = 0;

    // 1 = off, 0 = on (internal pull up resistor)
    int select = 1;
    
    
};

#endif
