#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include <Adafruit_MotorShield.h>

class MotorController
{
  public:

    // Constructor
    MotorController();

    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *leftMotor;
    Adafruit_DCMotor *rightMotor;
    
    void initializeMotors();
    void drive();
    void stopMotors();
    void shoot();
    void toggleGate();
    void calibrate();

    // Setters
    // Receiver data is in bytes
    void setLeftSpeed(byte leftSpeed);
    void setRightSpeed(byte rightSpeed);
    void setShoot(byte shoot);
    void setGate(byte gate);

    
    
    
  private:
  
    

    // Neutral stick positioning
    int leftNeutral = 124; // First guess without calibration
    int rightNeutral = 124; // First guess without calibration
    int neutralBump = 3; 

    // Speed Related
    int leftSpeed = leftNeutral;
    int rightSpeed = rightNeutral;

    // Shoot (left trigger)
    // 1 = off, 0 = on (internal pull up resistor)
    int shootState = 1;

    // Gate (right trigger)
    // 1 = off, 0 = on (internal pull up resistor)
    int gateState = 0;

    
};

#endif
