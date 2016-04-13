#include <BasicStepperDriver.h>
#include <DRV8834.h>
#include <Arduino.h>
#include <Servo.h>

#define RAYON 29
#define LED 13
boolean test = false;
boolean detacher = true;

//Pin pour DRV8834
#define MOTOR_STEPS 200
#define DIR1 7
#define DIR2 9
#define STEP 6
// Microstep control pour DRV8834, connection en parallèle des deux pins sur les deux drivers
#define MICROSTEP 4 //Le nombre de step de plus à faire pour un step (doit etre 2^n)
#define M0 12
#define M1 11
// Switch ON et OFF pour les drivers
#define SWITCH1 5
#define SWITCH2 10

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
  b.attach(BRAS, 570, 2400);
  if (angle > b.read())
  {
    for (int i = b.read(); i <= angle; i++) {
      b.write(i);
      delay(10);
    }
  }
  if (angle < b.read())
  {
    for (int i = b.read(); i >= angle; i--) {
      b.write(i);
      delay(10);
    }
  }
  delay(250);
  if (detacher == true)
  {
    b.detach();
  }
  detacher = true;
}

void pince(int var) {
  switch (var) {
    case 1: //Ouvrir
      p.write(100);
      break;
    case 2: //Fermer
      p.write(40);
      break;
    case 3: //Fermer sur le sac
      p.write(10);
      break;
  }
}

void deplacer(int d) {
  int pas = d / (RAYON * 2 * 3.1416) * 200 * MICROSTEP;
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
  stepper.move(-pas);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);

}

void rotationH()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, LOW);
  stepper.move(-136 * MICROSTEP);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}

void rotationAH()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, HIGH);
  stepper.move(136 * MICROSTEP);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}

void demirotationH()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, LOW);
  stepper.move(-105 * MICROSTEP);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}

void semirotationAH()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, HIGH);
  stepper.move(155 * MICROSTEP);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}

void semirotationH()
{
  digitalWrite(SWITCH1, HIGH);
  digitalWrite(SWITCH2, HIGH);
  digitalWrite(DIR2, LOW);
  stepper.move(-160 * MICROSTEP);
  digitalWrite(SWITCH1, LOW);
  digitalWrite(SWITCH2, LOW);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SWITCH1, OUTPUT);
  pinMode(SWITCH2, OUTPUT);
  p.attach(PINCE, 600, 2400);
  stepper.setRPM(20); //Vitesse en RPM
  stepper.setMicrostep(MICROSTEP); //Initialisation du microstep
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);

  //Mettre le code qui ne fonctionnera qu'une fois ici:
  while (test == false)
  {
    bras(158);
    delay(10000);
    pince(1);
    delay(500);
    deplacer(650);
    delay(1000);
    rotationH();
    delay(1000);
    deplacer(120);
    delay(600);
    bras(158);
    delay(500);
    pince(3);
    delay(1000);
    detacher = false;
    bras(35);
    delay(1000);
    deplacer(-110); //Ancien 130
    pince(1);   //Déposer le sac
    b.detach();
    delay(500);
    deplacer(90);
    delay(1000);
    rotationAH();
    delay(1000);
    bras(90);
    delay(500);
    deplacer(455); //Ancien 445
    delay(500);
    rotationH();
    delay(1000);
    bras(0);
    delay(1000);
    deplacer(-80); // Dépalcement en face anneau ancien -90
    delay(500);
    pince(2);  //Ramasser l'anneau
    delay(500);
    deplacer(100);
    delay(500);
    bras(160);
    delay(500);
    semirotationAH();
    delay(500);
    deplacer(740);
    delay(500);
    semirotationH();
    delay(500);
    deplacer(580);



    test = true;
  }
}
