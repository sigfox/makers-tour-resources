#include <Arduino.h>
#include <Wire.h>

void setup() {
  SerialUSB.begin(115200);
  SigFox.begin(19200);
  delay(500);

  ledBlueLight(HIGH);
  bool success;
  success = sendSigfox("1234CAFE");
  ledBlueLight(LOW);
  if (success){
    ledGreenLight(HIGH);
  }
  else{
    ledRedLight(HIGH);
  }

}

void loop() {
  while(SigFox.available()){
    SerialUSB.write(SigFox.read());
  }
}
bool sendSigfox(String frame){
  String status = "";
  char output;
  SerialUSB.print("AT$SF=");
  SerialUSB.println(frame);
  SigFox.print("AT$SF=");
  SigFox.print(frame);
  SigFox.print("\r");
  SerialUSB.println("Wait ..");
  while (!SigFox.available());

  while(SigFox.available()){
    output = (char)SigFox.read();
    status += output;
    SerialUSB.println(output);
    delay(10);
  }
  SerialUSB.print("Status \t");
  SerialUSB.println(status);
     if (status == "OK\r"){
      //Success :)
      return true;
    }
    else{
      return false;
    }
}
