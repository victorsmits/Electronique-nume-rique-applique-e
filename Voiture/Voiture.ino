// Code Voiture
// on a besoin des librairie SoftwareSerial & Servo
#include <SoftwareSerial.h>
#include <Servo.h>

// constante capteur de distance
int echopin = 4;
int trigpin = 5;
long distanceCm;
int duration;

// constante moteurs
int Speed =  3;
int Dir = 12;
int Brake = 9;
Servo servo;

// constante phares automatique
int DOUT_LED = 2;
int Y_save ;

SoftwareSerial BT(10,11); //RX,TX

void setup()
{
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  pinMode(Dir, OUTPUT);
  pinMode(Brake,OUTPUT);
  pinMode(DOUT_LED, OUTPUT);

  servo.attach(6);

  Serial.begin(9600);
  BT.begin(9600);

}

void loop()
{
  if(BT.available()>0)
  {
    // lecture des donnée du joystick reçus 
    int photoLed = analogRead(0);
    int X_plane = BT.read();
    int Y_plane = BT.read();

    // prise de mesure du capteur de distance
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    duration = pulseIn (echopin,HIGH);
    distanceCm = duration/58;

    if(distanceCm <= 40)
    {
      BT.write(distanceCm);  // enoie des données
    }

    // phares automatique
    if(photoLed <= 35)
    {
      digitalWrite(DOUT_LED, HIGH);
    }

    // https://www.arduino.cc/en/Tutorial/Knob
    // control des moteurs

    if (X_plane < 120)    // marche avant
    {
      digitalWrite(Brake, LOW);
      digitalWrite(Dir, HIGH);
      int X_map = map(X_plane, 0, 120, 255, 0);
      analogWrite(Speed, X_map);
    }
    if (X_plane > 130)    // marche arrier
    {
      digitalWrite(Brake, LOW);
      digitalWrite(Dir, LOW);
      int X_map = map(X_plane, 130, 255, 0, 255);
      analogWrite(Speed, X_map);
    }

    // control du servo moteur
    if(Y_plane != -1)
    {
      Y_save = Y_plane;
      servo.write(Y_plane);
    }
    else
    {
      servo.write(Y_save);
      analogWrite(Speed, 0);
      digitalWrite(DOUT_LED,LOW);
    }

  }
  delay(20);
}
