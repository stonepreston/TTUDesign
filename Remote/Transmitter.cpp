#include "Arduino.h"
#include "Transmitter.h"

Transmitter::Transmitter()  {


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
  SerialUSB.println(data[2]);
  SerialUSB.print("Right Trigger: ");
  SerialUSB.println(data[3]);
  SerialUSB.print("CheckSum: ");
  SerialUSB.println(createCheckSum());
}

void Transmitter::transmitData() {

  Serial1.write("U");
  
  Serial1.write("S");
  
  Serial1.write("A");
  
  Serial1.write(data[0]);
  
  Serial1.write(data[1]);
  
  Serial1.write(data[2]);
  
  Serial1.write(data[3]);
  
  Serial1.write(createCheckSum());
  
  delay(20);
  // Print debug data to console
  // debugData();

}

void Transmitter::setData(int capturedData[]) {

  for (int i=0; i <= dataSize - 1; i++){

      // Set elements of data array
      data[i] = capturedData[i];
   }

}






