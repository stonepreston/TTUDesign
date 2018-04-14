#include "Arduino.h"
#include "Transmitter.h"

// Create Transmitter object
Transmitter transmitter  = Transmitter();

int capturedData[4];

const int leftStickPin = A0; // analog
const int rightStickPin = A4; // analog
const int leftSelectPin = 11; // digital
const int calibrateButtonPin = 12; // digital

void setup()
{

  Serial.begin(9600);
  
  // make the SEL line an input
  pinMode(leftSelectPin,INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(leftSelectPin, HIGH);

  pinMode(calibrateButtonPin,INPUT);
}

void loop()
{
  
  captureData();
  transmitter.transmitData();
  
  
}

void captureData() {

  int leftVertical, rightVertical, select, calibrate;
  
  // read all values from the joystick
  leftVertical = analogRead(leftStickPin); // will be 0-1023
  rightVertical = analogRead(rightStickPin); // will be 0-1023
  select = digitalRead(leftSelectPin); // will be HIGH (1) if not pressed, and LOW (0) if pressed (pull-up)
  calibrate = digitalRead(calibrateButtonPin); // will be HIGH (1) if pressed, and LOW (0) if  not pressed (pull-down)

  capturedData[0] = map(leftVertical, 0, 1023, 0, 255);
  capturedData[1] = map(rightVertical, 0, 1023, 0, 255);
  capturedData[2] = select;
  capturedData[3] = calibrate;
  transmitter.setData(capturedData);
  
}

