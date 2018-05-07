#define echopin  2 // echo pin
#define trigpin 3 // Trigger pin
long duration;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int distanceCm, distanceInch;
// A4 SDA
//A5 SCL
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);  // Set the LCD I2C address

void setup()
{
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );

  lcd.home ();
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigpin,LOW); 
  delayMicroseconds(2);

  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);

  duration=pulseIn (echopin,HIGH);

  distanceCm= duration/58;
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distanceCm);
  lcd.print("  cm");
  delay(1200);

}
