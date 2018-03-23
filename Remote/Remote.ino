#include "Arduino.h"
#include "Transmitter.h"

Transmitter transmitter  = Transmitter();
int capturedData[3];

const int VERT = A0; // analog
const int HORIZ = A4; // analog
const int SEL = 4; // digital

void setup()
{

  Serial.begin(9600);
  

  // make the SEL line an input
  pinMode(SEL,INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(SEL,HIGH);
}

void loop()
{
  
  captureData();
  transmitter.transmitData();
  
}

void captureData() {

  int vertical, horizontal, select;
  
  // read all values from the joystick
  vertical = analogRead(VERT); // will be 0-1023
  horizontal = analogRead(HORIZ); // will be 0-1023
  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed

  capturedData[0] = vertical;
  capturedData[1] = horizontal;
  capturedData[3] = select;

  transmitter.setData(capturedData);
  
}

