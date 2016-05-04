#include <Arduino.h>
#include <Wire.h>

void setup() {
  SerialUSB.begin(115200);
  SigFox.begin(19200);
  delay(500);
  while (!SerialUSB);

  SerialUSB.println("** READY **");
  SigFox.print("AT/L\r");

}

void loop() {
  while (SigFox.available()) {
    SerialUSB.write(SigFox.read());
  }
  if (SerialUSB.available()){
    while (SerialUSB.available()){
      SigFox.write(SerialUSB.read());
    }
  }
}
