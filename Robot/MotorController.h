#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include <Servo.h>

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

    // Setters
    void setLeftSpeed(int leftSpeed);
    void setRightSpeed(int rightSpeed);
    void setLeftSelect(int leftSelect);
    void setRightSelect(int rightSelect);

    void calibrate();
    
    
  private:
  
    // Servo
    Servo shootingServo;  
    Servo gateServo;

    // Neutral stick positioning
    int leftNeutral = 243; // First guess without calibration
    int rightNeutral = 248; // First guess without calibration
    int neutralBump = 3; 

    // Speed Related
    int leftSpeed = leftNeutral;
    int rightSpeed = rightNeutral;


    // Left Select (shoot button)
    // 1 = off, 0 = on (internal pull up resistor)
    int leftSelect = 1;

    // Right Select (gate button)
    // 1 = off, 0 = on (internal pull up resistor)
    int rightSelect = 1;

    // Gate state
    bool gateClosed = false;
    
    
};

#endif
