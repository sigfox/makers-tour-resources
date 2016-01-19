#include <SoftwareSerial.h>
#define RX_PIN 4
#define TX_PIN 5
SoftwareSerial sigfox(RX_PIN,TX_PIN);

void setup(){
Serial.begin(9600);
sigfox.begin(9600);
sigfox.write("AT$SF=48 45 4c 4c 4f 20 57 4f 52 4c 44\r");
}
void loop(){
while (sigfox.available()){
Serial.write(sigfox.read());
}
}
