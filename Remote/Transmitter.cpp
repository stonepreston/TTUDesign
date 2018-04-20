#include "Arduino.h"
#include "Transmitter.h"

Transmitter::Transmitter()  {

  // Serial.begin is called in Remote setup, not needed here
  // Serial.begin(9600);

  Serial1.begin(9600);
  
  
}

byte Transmitter::createCheckSum() {

  // calculate checksum based on data
  return byte(data[0] + data[1] + data[2] + data[3]);
  
}

void Transmitter::debugData() {

  SerialUSB.println("U");
  SerialUSB.println("S");
  SerialUSB.println("A");
  SerialUSB.print("Left: ");
  SerialUSB.println(data[0]);
  SerialUSB.print("Right: ");
  SerialUSB.println(data[1]);
  SerialUSB.print("Left Trigger: ");
  SerialUSB.println(byte(data[2]));
  SerialUSB.print("Right Trigger: ");
  SerialUSB.println(byte(data[3]));
  SerialUSB.print("CheckSum: ");
  SerialUSB.println(createCheckSum());
}

void Transmitter::transmitData() {

  // Moving begin to constructor

  
  // xBee.begin(9600);
  Serial1.write("U");
  Serial1.write("S");
  Serial1.write("A");
  Serial1.write(data[0]);
  Serial1.write(data[1]);
  Serial1.write(byte(data[2]));
  Serial1.write(byte(data[3]));
  Serial1.write(createCheckSum());

  // Print debug data to console
  debugData();
  
  // Delay needed for consistent communication
  // Removing delay to see if it improves performance. I think the delays are fucking with things
  // delay(20);
}

void Transmitter::setData(int capturedData[]) {

  for (int i=0; i <= dataSize - 1; i++){

      // Set elements of data array
      data[i] = capturedData[i];
   }

}






