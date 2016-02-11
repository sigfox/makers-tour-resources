#include <SoftwareSerial.h>
#define MAX_DOWNLINK_WAITING_TIME 60000
#define ERROR_MSG "ERROR"

SoftwareSerial sigfox(5,4);

void setup(){
  Serial.begin(9600);
  sigfox.begin(9600);
  delay(300);
  sigfox.write("AT$SF=55 50 4c 49 4e 4b, 2, 1\r");
  String downlinkString;
  
  downlinkString = waitForDownlink();  
  if (downlinkString.equals(ERROR_MSG)){
    Serial.println("Invalid AT$SF command");
  }
  else{
    if (downlinkString.length() == 0){
      Serial.println("No downlink message"); 
    }
  }
  Serial.print("DOWNLINK:");
  Serial.println(downlinkString);

  
}
void loop(){
  
}
//Improve : Hook the RX/TX to the HW Serial pins (0,1), and use void serialEvent() instead of blocking
String waitForDownlink() {
  int start = millis();
  
  String buffer, reply;
  while (MAX_DOWNLINK_WAITING_TIME > (millis()-start)){
    while (sigfox.available()){
      buffer = sigfox.readStringUntil('\n');
      Serial.print("\t");
      Serial.println(buffer);
      while (buffer.startsWith("\n")){
        buffer.remove(0,1);
      }
      
      if (buffer.equals(ERROR_MSG)){
        return ERROR_MSG;
      }
      if (buffer.startsWith("+RX END")){
        return "";
      }
      if (buffer.startsWith("+RX=")){
        buffer.remove(0,4);
        return buffer;

      }
    }
  }
  return "";
}
