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
void deplacement(int vitesse,int DIR1,int DIR2,int delai) {
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
  // Temps de la procédure
  delay(delai);
}
  //Fonction avancer
void avancer(int vitesse,int delai) {
  // Sens vers l'avant
  DIR1=HIGH;
  DIR2=HIGH;
  deplacement(vitesse,DIR1,DIR2,delai);
}
 //Fonction reculer
void reculer(int vitesse,int delai) {
  // Sens vers l'arrière
  DIR1=LOW;
  DIR2=LOW;
  deplacement(vitesse,DIR1,DIR2,delai);
}
  //Fonction rotation à droite
void rotationD(int vitesse, int delai) {
  // Sens mixe pour tourner vers la droite
  DIR1=HIGH;
  DIR2=LOW;
  deplacement(vitesse,DIR1,DIR2,delai);
}
  //Fonction rotation à gauche
void rotationG(int vitesse, int delai) {
  // Sens mixe pour tourner vers la gauche
  DIR1=LOW;
  DIR2=HIGH;
  deplacement(vitesse,DIR1,DIR2,delai);
}
  //Freiner
void brake(int delai) {
  DIR1=LOW;
  DIR2=LOW;
  vitesse=0;
  deplacement(vitesse,DIR1,DIR2,delai);
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
  // put your main code here, to run repeatedly:
  // Cela sert à ramasser en continue les valeurs des capteurs

  // Par exemple, le led jaune de base va s'allumer seulement
  // lorsque le robot fait une rotation ou est à l'arrêt
   //if (DIR1==HIGH && DIR2==LOW) {
      //digitalWrite(LED, HIGH); }
   //else if (DIR1==LOW && DIR2==HIGH) {
      //digitalWrite(LED, HIGH); }
   //else {
      //digitalWrite(LED, LOW); }




    // Ici on écrit le code! Avec les fonctions avancer, reculer
    // brake, rotationD et rotationG sous la forme (vitesse,delai)
    // vitesse étant compris entre 0 et 255 (8bit)
    // delai étant en ms

avancer(130,15000);
digitalWrite(LED,HIGH);
reculer(130,15000);
}
