#include "Arduino.h"
#include "Transmitter.h"
#include "Bounce2.h"

// Create Transmitter object
Transmitter transmitter  = Transmitter();

// Create Bounce objects
Bounce leftTriggerDebouncer = Bounce(); 
Bounce rightTriggerDebouncer = Bounce(); 

int capturedData[4];

const int leftStickPin = A3; // analog
const int rightStickPin = A0; // analog
const int leftTriggerPin = 6; // digital
const int rightTriggerPin = 3; // digital

void setup()
{

  // SerialUSB.begin(9600);
  Serial1.begin(9600);

  // Wait for serial ports to open
  // while (!SerialUSB);
  while (!Serial1);

  Serial1.print("W7001\r\n");

  // Enable pullup resistor for left trigger
  pinMode(leftTriggerPin, INPUT_PULLUP); 
  
  // Enable pullup resistor for right trigger
  pinMode(rightTriggerPin, INPUT_PULLUP); 

  leftTriggerDebouncer.attach(leftTriggerPin);
  leftTriggerDebouncer.interval(5); 

  rightTriggerDebouncer.attach(rightTriggerPin);
  rightTriggerDebouncer.interval(5); 
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

  // Update bounce objects
  leftTriggerDebouncer.update();
  rightTriggerDebouncer.update();
  
  leftTrigger = leftTriggerDebouncer.read(); // will be HIGH (1) if not pressed, and LOW (0) if pressed (pull-up)
  rightTrigger = rightTriggerDebouncer.read(); // will be HIGH (1) if pressed, and LOW (0) if  not pressed (pull-down)

  capturedData[0] = map(leftVertical, 0, 1023, 0, 255);
  capturedData[1] = map(rightVertical, 0, 1023, 0, 255);
  capturedData[2] = leftTrigger;
  capturedData[3] = rightTrigger;
  transmitter.setData(capturedData);
  
}

