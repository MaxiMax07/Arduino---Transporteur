#include <BasicStepperDriver.h>
#include <DRV8834.h>
#include <Arduino.h>
#include <Servo.h>

#define RAYON 29
#define LED 13

//Pin pour DRV8834
#define MOTOR_STEPS 200
#define DIR1 7
#define STEP1 6
#define DIR2 8
#define STEP2 9
// Microstep control pour DRV8834, connection en parallèle des deux pins sur les deux drivers
#define MICROSTEP 1 //Le nombre de step de plus à faire pour un step (doit etre 2^n)
#define M0 12
#define M1 11
// Switch ON et OFF pour les drivers
#define SWITCH1 5
#define SWITCH2 10

//Initialisation des steppers moteurs
DRV8834 Stepper1(MOTOR_STEPS, DIR1, STEP1, M0, M1);
DRV8834 Stepper2(MOTOR_STEPS, DIR2, STEP2, M0, M1);

//Pin pour servo
#define PINCE 2
#define BRAS 3

//Initilisation des servos
Servo pince;
Servo bras;

void deplacement(int d)
{
  int pas = d / (RAYON * 2 * 3.1416) * 200 * MICROSTEP;
  for (int i = 0; i < pas; i++)
  {
digitalWrite(SWITCH1,HIGH);
digitalWrite(LED,HIGH);
Stepper1.move(4);
digitalWrite(SWITCH1,LOW);
digitalWrite(LED,LOW);
delay(10);
digitalWrite(SWITCH2,HIGH);
Stepper2.move(-4);
digitalWrite(SWITCH2,LOW);
delay(10);
  }
}

void tournerD()
{
  for (int i = 0; i < 66; i++)
  {
digitalWrite(SWITCH1,HIGH);
digitalWrite(LED,HIGH);
Stepper1.move(146);
digitalWrite(SWITCH1,LOW);
digitalWrite(LED,LOW);
digitalWrite(SWITCH2,HIGH);
Stepper2.move(146);
digitalWrite(SWITCH2,LOW);
  }
}

void tournerG()
{
  for (int i = 0; i < 66; i++)
  {
digitalWrite(SWITCH1,HIGH);
digitalWrite(LED,HIGH);
Stepper1.move(146);
digitalWrite(SWITCH1,LOW);
digitalWrite(LED,LOW);
digitalWrite(SWITCH2,HIGH);
Stepper2.move(146);
digitalWrite(SWITCH2,LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH1,OUTPUT);
  pinMode(SWITCH2,OUTPUT);
  pince.attach(PINCE, 600, 2400);
  bras.attach(BRAS, 600, 2400);
  Stepper1.setRPM(20*MICROSTEP); //Vitesse en RPM
  Stepper2.setRPM(20*MICROSTEP);
  Stepper1.setMicrostep(MICROSTEP); //Initialisation du microstep
  Stepper2.setMicrostep(MICROSTEP);

}

void pince(int var) {
  switch (var) {
    case 1: //Ouvrir
      p.write(100);
      break;
    case 2: //Fermer
      p.write(10);
      break;
    case 3: //Fermer sur le sac
      p.write(30); // À remplir
      break;

void loop() {
  // put your main code here, to run repeatedly:

deplacement(600);
delay(2000);
}
