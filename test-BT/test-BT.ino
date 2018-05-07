#include <SoftwareSerial.h>

SoftwareSerial BT(10,11); //RX,TX

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  BT.write(1);
  Serial.println(1);
}
