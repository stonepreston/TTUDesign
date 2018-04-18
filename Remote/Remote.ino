#include "Arduino.h"
#include "Transmitter.h"

// Create Transmitter object
Transmitter transmitter  = Transmitter();

int capturedData[4];

const int leftStickPin = A0; // analog
const int rightStickPin = A4; // analog
const int leftTriggerPin = 11; // digital
const int rightTriggerPin = 12; // digital

void setup()
{

  Serial.begin(9600);
  
  // make the SEL line an input
  pinMode(leftTriggerPin,INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(leftTriggerPin, HIGH);

  pinMode(rightTriggerPin,INPUT);
}

void loop()
{
  
  captureData();
  transmitter.transmitData();
  
  
}

void captureData() {

  int leftVertical, rightVertical, leftTrigger, rightTrigger;
  
  // read all values from the joystick
  leftVertical = analogRead(leftStickPin); // will be 0-1023
  rightVertical = analogRead(rightStickPin); // will be 0-1023
  leftTrigger = digitalRead(leftTriggerPin); // will be HIGH (1) if not pressed, and LOW (0) if pressed (pull-up)
  rightTrigger = digitalRead(rightTriggerPin); // will be HIGH (1) if pressed, and LOW (0) if  not pressed (pull-down)

  capturedData[0] = map(leftVertical, 0, 1023, 0, 255);
  capturedData[1] = map(rightVertical, 0, 1023, 0, 255);
  capturedData[2] = leftTrigger;
  capturedData[3] = rightTrigger;
  transmitter.setData(capturedData);
  
}

