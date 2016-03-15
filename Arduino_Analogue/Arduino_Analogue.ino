// Nom pour les pin directionnel du motorshield
#define ENCODER1 2
#define ENCODER2 3
#define M1DIR 7
#define M2DIR 8
#define M1PWM 9
#define M2PWM 10
#define LED 13

// Déclaration des variables
volatile int g_vToursM1;
volatile int g_vToursM2;
volatile int rawsensorValueA = 0; // variable to store the value coming from the sensor
volatile int rawsensorValueB = 0;
volatile int sensorcount0B = 0;
volatile int sensorcount1B = 0;
volatile int sensorcount0A = 0;
volatile int sensorcount1A = 0;
volatile boolean test = false;

// Déclaration des constantes liées aux composantes
const float RAYON = 1.75;
#define FREINAGE 0 //(Distance en clics)
#define ENTRE_ROUES 9.3 // Distance entre les roues en cm

//Permet d'avoir le code fonctionnel
boolean code = true;


//Fonction lire donnée encodeur
void setencodeur1()
{
  rawsensorValueA = analogRead(5);
  if (rawsensorValueA < 800) { //Min value is 700 and max value is 900, so state chance can be done at 600.
    sensorcount0A = 1;
  }
  else {
    sensorcount0A = 0;
  }
}

void setencodeur2()
{
  rawsensorValueB = analogRead(4);
  if (rawsensorValueB < 800) { //Min value is 700 and max value is 900, so state chance can be done at 600.
    sensorcount0B = 1;
  }
  else {
    sensorcount0B = 0;
  }
}

void encodeur1()
{
  rawsensorValueA = analogRead(5);
  if (rawsensorValueA < 800) { //Min value is 400 and max value is 800, so state chance can be done at 600.
    sensorcount1A = 1;
  }
  else {
    sensorcount1A = 0;
  }
  if (sensorcount1A != sensorcount0A) {
    g_vToursM1++;
  }
  sensorcount0A = sensorcount1A;
}

void encodeur2()
{
  rawsensorValueB = analogRead(4);
  if (rawsensorValueB < 800) { //Min value is 700 and max value is 900, so state chance can be done at 600.
    sensorcount1B = 1;
  }
  else {
    sensorcount1B = 0;
  }
  if (sensorcount1B != sensorcount0B)
  {
    test = true;
  }
  else if (sensorcount1B == sensorcount0B & test == true)
  {
    g_vToursM2++;
    test = false;
  }
  sensorcount0B = sensorcount1B;

}
//Fonctions pour le déplacement

//Fonction de base
void deplacement(byte in_iVitesse, int in_iDir1, int in_iDir2, int in_iDistance)
{
  //Valeur nécessairement positif puisque analogue (8 bit)
  byte in_iVitesse1 = in_iVitesse;
  byte in_iVitesse2 = in_iVitesse;
  if (in_iDir1 == 123)
  {
    in_iVitesse1 = 0;
    in_iDir1 = LOW;
  }
  if (in_iDir2 == 123)
  {
    in_iVitesse2 = 0;
    in_iDir2 = LOW;
  }
  if (in_iVitesse < 0)
  {
    in_iVitesse = -in_iVitesse;
  }
  //Valeurs max pour 3V estimer a 130 mais tests à faire encore
  if (in_iVitesse >= 130)
  {
    in_iVitesse = 130;
  }
  // Direction et in_iVitesse moteur 1
  int l_iTours = dis(in_iDistance);
  // Remise à zero des valeurs
  analogWrite(M1PWM, in_iVitesse1);
  digitalWrite(M1DIR, in_iDir1);
  // Direction et in_iVitesse moteur 2
  analogWrite(M2PWM, in_iVitesse2);
  digitalWrite(M2DIR, in_iDir2);
  int l_iToursMoyen = 0;
  g_vToursM1 = 0; g_vToursM2 = 0;
  setencodeur1();
  setencodeur2();
  digitalWrite(LED, HIGH);
  while ( l_iTours > g_vToursM1 || l_iTours > g_vToursM2  )
  {
    encodeur1();
    encodeur2();
    delay(50);
  }
  while (l_iTours > g_vToursM1)
  {
    analogWrite(M1PWM, 0);
    encodeur2();
    delay(50);
  }
  while (l_iTours > g_vToursM2)
  {
    analogWrite(M2PWM, 0);
    encodeur1();
    delay(50);
  }
  analogWrite(M1PWM, 0);
  analogWrite(M2PWM, 0);
  digitalWrite(LED,LOW);
}
//Fonction avancer
void avancer(byte in_iVitesse, int in_iDistance) {
  // Sens vers l'avant
  deplacement(in_iVitesse, HIGH, HIGH, in_iDistance);
}
//Fonction reculer
void reculer(byte in_iVitesse, int in_iDistance) {
  // Sens vers l'arrière
  deplacement(in_iVitesse, LOW, LOW, in_iDistance);
}
//Fonction rotation à droite
void rotationG(byte in_iVitesse, int angle) {
  //Calcul de la distance à parcourir / 2 car c'est la moyenne deux deux roues
  int in_iDistance = ENTRE_ROUES * 3.1413 * 360 / angle;
  // Sens mixe pour tourner vers la droite
  deplacement(in_iVitesse, HIGH, 123, in_iDistance);
}
//Fonction rotation à gauche
void rotationD(byte in_iVitesse, int angle) {
  //Calcul de la distance à parcourir / 2 car c'est la moyenne deux deux roues
  int in_iDistance = ENTRE_ROUES * 3.1413 * 360 / angle;
  // Sens mixe pour tourner vers la gauche
  deplacement(in_iVitesse, 123 , HIGH, in_iDistance);
}
//Freiner
void brake() {
  analogWrite(M1PWM, 0);
  digitalWrite(M1DIR, LOW);
  // Direction et in_iVitesse moteur 2
  analogWrite(M2PWM, 0);
  digitalWrite(M2DIR, LOW);
}

//Nombre de clics pour distance
int dis(int in_iDistance) {
  return in_iDistance / (RAYON * 2 * 3.1416) * 16 - FREINAGE;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M1DIR, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(6000);
  avancer(25, 100);
  rotationG(25, 90);
  avancer(25, 100);
  rotationG(25, 90);
  brake();
}
