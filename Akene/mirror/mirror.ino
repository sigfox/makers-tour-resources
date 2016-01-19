#include <SoftwareSerial.h>

SoftwareSerial sigfox(4,5);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sigfox.begin(9600);
  
  delay(2000);
  Serial.println("OK");

}

void loop() {
  // put your main code here, to run repeatedly:
  while (sigfox.available()){
    Serial.write(sigfox.read());
  }
  while (Serial.available()){
    sigfox.write(Serial.read());
  }
}
