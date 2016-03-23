#include <BasicStepperDriver.h>
#include <DRV8834.h>
// #include <Arduino.h> Nécessaire???
#include <Servo.h>

#define RAYON 58

//Pin pour DRV8834
#define MOTOR_STEPS 200
#define DIR1 6
#define STEP1 7
#define DIR2 8
#define STEP2 9
// Microstep control pour DRV8834, connection en parallèle des deux pins sur les deux drivers
#define MICROSTEP 2 //Le nombre de step de plus à faire pour un step (doit etre 2^n)
#define M0 10
#define M1 11

//Initialisation des steppers moteurs
DRV8834 Stepper1(MOTOR_STEPS, DIR1, STEP1, M0, M1);
DRV8834 Stepper2(MOTOR_STEPS, DIR2, STEP2, M0, M1);

//Pin pour servo
#define PINCE 1
#define BRAS 2

//Initilisation des servos
Servo pince;
Servo bras;

void deplacement(int d)
{
  int pas = d / (RAYON * 2 * 3, 1416) * 200 * MICROSTEP;
  for (int i = 0; i < pas; i++)
  {
    Stepper1.move(1);
    Stepper2.move(1);
  }
}

void setup() {
  // put your setup code here, to run once:
  pince.attach(PINCE, 600, 2400);
  bras.attach(BRAS, 600, 2400);
  Stepper1.setRPM(30*MICROSTEP); //Vitesse en RPM
  Stepper2.setRPM(30*MICROSTEP);
  Stepper1.setMicrostep(MICROSTEP); //Initialisation du microstep
  Stepper2.setMicrostep(MICROSTEP);
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
  delay(3000);
  deplacement(200); //Distance en mm


}
