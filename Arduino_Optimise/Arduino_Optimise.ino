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

// Déclaration des constantes liées aux composantes
const float RAYON = 1.75;
#define FREINAGE 6 //(Distance en clics)

//Permet d'avoir le code fonctionnel
boolean code = true;

//Fonctions pour le déplacement

//Fonction de base
void deplacement(int in_iVitesse, int in_iDir1, int in_iDir2, int in_iDistance) {
  //Valeur nécessairement positif puisque analogue (8 bit)
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
  analogWrite(M1PWM, in_iVitesse);
  digitalWrite(M1DIR, in_iDir1);
  // Direction et in_iVitesse moteur 2
  analogWrite(M2PWM, in_iVitesse);
  digitalWrite(M2DIR, in_iDir2);
  int l_iToursMoyen = (g_vToursM1 + g_vToursM2) / 2;
  while ( l_iTours > l_iToursMoyen )
  {
    Serial.print("Tours M1:");
    Serial.println(g_vToursM1);
    Serial.print("Tours M2:");
    Serial.println(g_vToursM2);
    l_iToursMoyen = (g_vToursM1 + g_vToursM2) / 2;
    delay(200);
  }
  g_vToursM1 = 0; g_vToursM2 = 0;
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
void rotationG(byte in_iVitesse, int in_iDistance) {
  // Sens mixe pour tourner vers la droite
  deplacement(in_iVitesse, HIGH, LOW, in_iDistance);
}
//Fonction rotation à gauche
void rotationD(byte in_iVitesse, int in_iDistance) {
  // Sens mixe pour tourner vers la gauche
  deplacement(in_iVitesse, LOW, HIGH, in_iDistance);
}
//Freiner
void brake() {
analogWrite(M1PWM, 0);
  digitalWrite(M1DIR, 0);
  // Direction et in_iVitesse moteur 2
  analogWrite(M2PWM, 0);
  digitalWrite(M2DIR, 0);
}

// Fonction pour compter le nombre de tours -- ISR
void count1() {
  g_vToursM1++;
}
void count2() {
  g_vToursM2++;
}

//Nombre de clics pour distance
int dis(int in_iDistance) {
  return in_iDistance / (RAYON * 2 * 3,1416) * 16 - FREINAGE;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M1DIR, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ENCODER1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER1), count1, CHANGE);
  pinMode(ENCODER2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER2), count2, CHANGE);
  //Code définitif ici, qui ne recommence pas à l'infini

}

void loop() {


  //Code qui tourne qu'une fois ici!
  if (code == true) {




    code = false ;
  }
}
