#include <SoftwareSerial.h>

SoftwareSerial BT(10,11); //RX,TX

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  // long Data = BT.read();
  Serial.println(BT.read());
  delay(100);
}
