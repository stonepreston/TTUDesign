#include "Arduino.h"
#include "Transmitter.h"

// Create Transmitter object
Transmitter transmitter  = Transmitter();

int capturedData[4];

const int leftStickPin = A0; // analog
const int rightStickPin = A4; // analog
const int leftSelectPin = 11; // digital
const int rightSelectPin = 13; // digital


void setup()
{

  Serial.begin(9600);
  
  // set pin modes for digital inputs
  pinMode(leftSelectPin,INPUT);
  pinMode(rightSelectPin, INPUT);

  // turn on the pull-up resistor for the SEL lines 
  digitalWrite(leftSelectPin, HIGH);
  digitalWrite(rightSelectPin, HIGH);
  

  
}

void loop()
{
  
  captureData();
  transmitter.transmitData();
  
  
}

void captureData() {

  int leftVertical, rightVertical, leftSelect, rightSelect;
  
  // read all values from the joystick
  leftVertical = analogRead(leftStickPin); // will be 0-1023
  rightVertical = analogRead(rightStickPin); // will be 0-1023
  leftSelect = digitalRead(leftSelectPin); // will be HIGH (1) if not pressed, and LOW (0) if pressed (pull-up)
  rightSelect = digitalRead(rightSelectPin); // will be HIGH (1) if not pressed, and LOW (0) if pressed (pull-up)
  

  // Map left and right analog sticks to 0-255 range
  capturedData[0] = map(leftVertical, 0, 1023, 0, 255);
  capturedData[1] = map(rightVertical, 0, 1023, 0, 255);
  capturedData[2] = leftSelect;
  capturedData[3] = rightSelect;
  transmitter.setData(capturedData);
  
}

