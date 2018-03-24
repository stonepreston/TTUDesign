#include "Arduino.h"
#include "Transmitter.h"

// Create Transmitter object
Transmitter transmitter  = Transmitter();

int capturedData[3];

const int leftStickPin = A0; // analog
const int rightStickPin = A4; // analog
const int leftSelectPin = 4; // digital

void setup()
{

  Serial.begin(9600);
  

  // make the SEL line an input
  pinMode(leftSelectPin,INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  
}

void loop()
{
  
  captureData();
  transmitter.transmitData();
  
}

void captureData() {

  int leftVertical, rightVertical, select;
  
  // read all values from the joystick
  leftVertical = analogRead(leftStickPin); // will be 0-1023
  rightVertical = analogRead(rightStickPin); // will be 0-1023
  select = digitalRead(leftSelectPin); // will be HIGH (1) if not pressed, and LOW (0) if pressed

  capturedData[0] = leftVertical;
  capturedData[1] = rightVertical;
  capturedData[3] = select;

  transmitter.setData(capturedData);
  
}

