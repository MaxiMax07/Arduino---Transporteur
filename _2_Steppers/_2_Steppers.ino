#include <BasicStepperDriver.h>
#include <DRV8834.h>
#include <Arduino.h>
#include <Servo.h>

#define RAYON 29
#define LED 13
boolean test = true;

//Pin pour DRV8834
#define MOTOR_STEPS 200
#define DIR1 5
#define DIR2 6
#define STEP 7
// Microstep control pour DRV8834, connection en parallèle des deux pins sur les deux drivers
#define MICROSTEP 2 //Le nombre de step de plus à faire pour un step (doit etre 2^n)
#define M0 8
#define M1 9
// Switch ON et OFF pour les drivers
#define SWITCH1 10
#define SWITCH2 11

//Initialisation des steppers moteurs
DRV8834 stepper(MOTOR_STEPS, DIR1, STEP, M0, M1);

//Pin pour servo
#define PINCE 2
#define BRAS 3

//Initilisation des servos
Servo p; //Pince
Servo b; //Bras

//Utiliser la bras lentement
void bras(int angle) {
  for (int i = b.read(); i <= angle; i++) {
    b.write(i);
    delay(10);
  }
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

  }
}

void deplacer(int d) {
  int pas = - d / (RAYON * 2 * 3.1416) * 200 * MICROSTEP;
  boolean a;
  if (pas > 0) {
    a = HIGH;
  }
  else {
    a = LOW;
  }

  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, a);
  stepper.move(pas);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);

}

void tournerD()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, LOW);
  stepper.move(-66); //Á calibrer
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}

void tournerG()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, HIGH);
  stepper.move(66);  //Á calibrer
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SWITCH1, OUTPUT);
  pinMode(SWITCH2, OUTPUT);
  p.attach(PINCE, 600, 2400);
  b.attach(BRAS, 600, 2400);
  stepper.setRPM(20); //Vitesse en RPM
  stepper.setMicrostep(MICROSTEP); //Initialisation du microstep
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);

  deplacer(600);

  //Mettre le code qui ne fonctionnera qu'une fois ici:
  while (test == false)
  {

    bras(35);


  test = true;
  }
}
