#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Transmitter.h"

Transmitter::Transmitter() :  xBee(2,3) {

  Serial.begin(9600);
  
}


byte Transmitter::createCheckSum() {

  // calculate checksum based on data
  return byte(data[0] + data[1] + data[2]);
  
}

void Transmitter::debugData() {

  Serial.println("U");
  Serial.println("S");
  Serial.println("A");
  Serial.print("Left: ");
  Serial.println(byte(data[0]));
  Serial.print("Right: ");
  Serial.println(byte(data[1]));
  Serial.print("Select: ");
  Serial.println(byte(data[2]));
  Serial.print("CheckSum: ");
  Serial.println(createCheckSum());
}

void Transmitter::transmitData() {

  xBee.begin(9600);
  xBee.write("U");
  xBee.write("S");
  xBee.write("A");
  xBee.write(byte(data[0]));
  xBee.write(byte(data[1]));
  xBee.write(byte(data[2]));
  xBee.write(createCheckSum());

  // Print debug data to console
  debugData();
  
  // Delay needed for consistent communication
  delay(200);
}

void Transmitter::setData(int capturedData[]) {

  for (int i=0; i <= dataSize - 1; i++){

      // Set elements of data array
      data[i] = capturedData[i];
   }

}






