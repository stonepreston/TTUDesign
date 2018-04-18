#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Transmitter.h"

Transmitter::Transmitter() :  xBee(2,3) {

  xBee.begin(9600);
  
  
}

byte Transmitter::createCheckSum() {

  // calculate checksum based on data
  return byte(data[0] + data[1] + data[2] + data[3]);
  
}

void Transmitter::debugData() {

  Serial.println("U");
  Serial.println("S");
  Serial.println("A");
  Serial.print("Left: ");
  Serial.println(data[0]);
  Serial.print("Right: ");
  Serial.println(data[1]);
  Serial.print("Left Select: ");
  Serial.println(data[2]);
  Serial.print("Right Select: ");
  Serial.println(data[3]);
  Serial.print("CheckSum: ");
  Serial.println(createCheckSum());
}

void Transmitter::transmitData() {

  xBee.write("U");
  xBee.write("S");
  xBee.write("A");
  xBee.write(data[0]);
  xBee.write(data[1]);
  xBee.write(data[2]);
  xBee.write(data[3]);
  xBee.write(createCheckSum());

  // Print debug data to console
  //debugData();
  
}

void Transmitter::setData(int capturedData[]) {

  for (int i=0; i <= dataSize - 1; i++){

      // Set elements of data array
      data[i] = capturedData[i];
   }

}






