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
    // Receiver data is in bytes
    void setLeftSpeed(byte leftSpeed);
    void setRightSpeed(byte rightSpeed);
    void setSelect(byte select);
    void setCalibration(byte calibration);

    void calibrate();
    
    
  private:
  
    // Servo
    Servo shootingServo;  

    // Neutral stick positioning
    int leftNeutral = 243; // First guess without calibration
    int rightNeutral = 248; // First guess without calibration
    int neutralBump = 3; 

    // Speed Related
    int leftSpeed = leftNeutral;
    int rightSpeed = rightNeutral;

    // Calibration
    // 0 = off, 1 = on (pull down resistor)
    int calibration = 0;


    // Select (shoot button)
    // 1 = off, 0 = on (internal pull up resistor)
    int select = 1;

    // Gate
    bool gateClosed = false;
    
    
};

#endif
