#include <Arduino.h>
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  SigFox.begin(19200);
  
  SerialUSB.println("REady");
  SigFox.print("+++");
  delay(500);

  SigFox.print("AT$SF=0123CAFE");
  SigFox.print("\r");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (SigFox.available()){
    SerialUSB.write(SigFox.read());
  }
}
