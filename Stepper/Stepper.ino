#include <Servo.h>

#define RAYON 58

int pas=0;

Servo pince;
Servo bras;

void distance(int d)
{
  int pas=d/(RAYON*2*3,1416)*200;
}

void setup() {
  // put your setup code here, to run once:
  pince.attach(9, 600, 2400);
  bras.attach(10);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  bras.write(90);
  delay(1000);
  pince.write(90);
  delay(1000);
  bras.write(180);
  delay(1000);
  pince.write(180);
  delay(1000);
  bras.write(0);
  delay(1000);
  pince.write(0);
distance(65); //Distance en mm

}
