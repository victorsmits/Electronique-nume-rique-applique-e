#include <Servo.h>

int Speed =  11;
int Dir = 13;
int Brake = 8;

int X_plane = 0;
int Y_plane = 0;
int SNS1;

Servo servo;

void setup() {

  //Setup Channel A
  pinMode(Dir, OUTPUT); //Initiates Motor Channel A pin
  pinMode(Brake, OUTPUT); //Initiates Brake Channel A pin

  servo.attach(6);

  Serial.begin(9600);

}

void loop(){
  X_plane = analogRead(A3);
  Y_plane = analogRead(A4);
  SNS1 = analogRead(A1);

  int Y_map = map(Y_plane, 0, 1023, 0, 180);     //https://www.arduino.cc/en/Tutorial/Knob
  servo.write(Y_map);

  if (X_plane <= 535)
  {
    digitalWrite(Brake,LOW);
    digitalWrite(Dir, HIGH);
    int X_map = map(X_plane, 0, 535, 255, 0);
    Serial.println(X_plane);
    analogWrite(Speed, X_map);
  }

  if (X_plane > 535)
  {
    digitalWrite(Brake,LOW);
    digitalWrite(Dir, LOW);
    int X_map = map(X_plane, 535, 1023, 0, 255);
    Serial.println(X_plane);
    analogWrite(Speed, X_map);
  }
  //delay(1000);
}
