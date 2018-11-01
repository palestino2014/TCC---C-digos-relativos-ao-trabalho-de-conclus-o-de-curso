#include <Servo.h>

#define SERVO 6 // Porta Digital 6 PWM
#define SERVO1 5 
#define SERVO2 3

Servo s;
Servo w;// Variável Servo
Servo t;
int pos; // Posição Servo
int pos1;
int pos2;

void setup ()
{
  s.attach(SERVO);
  w.attach(SERVO1);
  t.attach(SERVO2);
  Serial.begin(9600);
  s.write(pos); // Inicia motor posição zero
  w.write(pos1);
  t.write(pos2);
}

void loop()
{
  for(pos = 0; pos < 90; pos++)
  {
    s.write(pos);
  delay(30);
  }
delay(1000);
  for(pos = 90; pos >= 0; pos--)
  {
    s.write(pos);
    delay(30);
  }

    for(pos1 = 0; pos1 < 120; pos1++)
  {
    w.write(pos1);
  delay(30);
  }
delay(1000);
  for(pos1 = 120; pos1 >= 0; pos1--)
  {
    w.write(pos1);
    delay(30);
  }


  
    for(pos2 = 0; pos2 < 120; pos2++)
  {
    t.write(pos2);
  delay(30);
  }
delay(1000);
  for(pos2 = 120; pos2 >= 0; pos2--)
  {
    t.write(pos2);
    delay(30);
  }



}



