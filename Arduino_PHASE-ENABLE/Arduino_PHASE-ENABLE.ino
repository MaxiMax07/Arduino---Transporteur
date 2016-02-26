  // Nom pour les pin directionnel du motorshield
const unsigned char M1DIR = 7;
const unsigned char M2DIR = 8;
const unsigned char M1PWM = 9;
const unsigned char M2PWM = 10;
const unsigned char LED = 13;
  // Déclaration des variables
int vitesse;
int delai;
int DIR1;
int DIR2;

  //Fonctions pour le déplacement

  //Fonction de base
void deplacement(int vitesse,int DIR1,int DIR2) {
    //Valeurs max pour 3V estimer a 70 mais tests à faire encore
  if (vitesse>=130) vitesse = 130;
    //Valeur nécessairement positif puisque analogue (8 bit)
  if (vitesse<0) vitesse=-vitesse;
  // Direction et vitesse moteur 1
  analogWrite(M1PWM,vitesse);
  digitalWrite(M1DIR,DIR1);
  // Direction et vitesse moteur 2
  analogWrite(M2PWM,vitesse);
  digitalWrite(M2DIR,DIR2);
}
  //Fonction avancer
void avancer(int vitesse) {
  // Sens vers l'avant
  DIR1=HIGH;
  DIR2=HIGH;
  deplacement(vitesse,DIR1,DIR2);
}
 //Fonction reculer
void reculer(int vitesse) {
  // Sens vers l'arrière
  DIR1=LOW;
  DIR2=LOW;
  deplacement(vitesse,DIR1,DIR2);
}
  //Fonction rotation à droite
void rotationG(int vitesse) {
  // Sens mixe pour tourner vers la droite
  DIR1=HIGH;
  DIR2=LOW;
  deplacement(vitesse,DIR1,DIR2);
}
  //Fonction rotation à gauche
void rotationD(int vitesse) {
  // Sens mixe pour tourner vers la gauche
  DIR1=LOW;
  DIR2=HIGH;
  deplacement(vitesse,DIR1,DIR2);
}
  //Freiner
void brake(int delai) {
  DIR1=LOW;
  DIR2=LOW;
  vitesse=0;
  deplacement(vitesse,DIR1,DIR2);
}

void setup() {
  // put your setup code here, to run once:

  //On setup toute les pins directionnelles et le LED
  Serial.begin(9600);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M1DIR, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
 digitalWrite(LED,HIGH);
avancer(60);
delay(3500);
  digitalWrite(LED,LOW);
reculer(60);
delay(3500);
rotationD(60);
delay(2000);
rotationG(60);
delay(2000);

}
