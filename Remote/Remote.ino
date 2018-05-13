// Code Remote
//  besoin des librairie Wire, LiquidCrystal_I2C & SoftwareSerial
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

int distanceCm;
int Y_save = 0;
int buzzer = 3;
boolean buzstate = true;

unsigned int freq;

// A4 SDA
// A5 SCL
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);  // Set the LCD I2C address

SoftwareSerial BT(10,11); //RX,TX

void setup()
{
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  // reception des donnée du capteur de distance
  distanceCm = BT.read();
  Serial.println(distanceCm);

  // lecture des donnée du joystick
  int X_plane = analogRead(A2);
  int Y_plane = analogRead(A1);
  int X_map = map(X_plane,0,1023,0,255);
  int Y_map = map(Y_plane,0,1023,0,180);

  // affichage de la distance sur l'écran LCD
  if(distanceCm != -1)
  {
    buzstate = true;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance:");
    lcd.print(distanceCm);
    lcd.print(" cm");
  }
  if(distanceCm == -1)
  {
    buzstate = false;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance:too far");
  }

  // déclenchement du buzzer quand la distance est inferieur a 40cm
  if (distanceCm <= 40 && buzstate == true)
  {
    int freq = map(distanceCm * 58,0,2900,600,50);
    int Time = map(distanceCm * 58,0,2900,100,1200);
    tone(buzzer, freq, Time);
  }

  // envoie des donée a la voiture
  BT.write(X_map);
  int delta = Y_map - Y_save;
  Serial.println(delta);

  // marge de sécuritée pour l'envoie de l'axe Y
  if(delta > 5)
  {
    Y_save = Y_map;
    BT.write(Y_map);
    // Serial.println(Y_map);
  }
  if(delta < -5)
  {
    Y_save = Y_map;
    BT.write(Y_map);
    // Serial.println(Y_map);
  }
  else
  {
    BT.write(Y_save);
  }

  delay(20);
}
