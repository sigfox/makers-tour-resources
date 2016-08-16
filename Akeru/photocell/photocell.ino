
#include <SoftwareSerial.h>
#define PHOTO_PIN A0
#define SAMPLE_RATE 2000

SoftwareSerial sigfox(5,4);

int brightness;


void setup(void) {
  Serial.begin(9600); 
  sigfox.begin(9600);  
}
     
void loop(void) {
  brightness = analogRead(PHOTO_PIN); 
  Serial.println(brightness);
  sendSigfox(String(brightness, HEX));
  delay(SAMPLE_RATE);
}
void sendSigfox(String frame){
 if (frame.length() % 2 != 0){
   frame = "0"+frame;
 }
  
 Serial.print("Sending  ");
 Serial.println(frame);
;
 sigfox.write("AT$SF=");
 sigfox.print(frame);
 sigfox.write("\n");
 
}
