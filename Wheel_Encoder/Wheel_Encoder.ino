//Encoder pins doivent être 2 ou 3 car c'est les seules compatibles avec attachInterrupt
double encoderPin1 = 2, encoderPin2=3,
    M1DIR = 7,
    M2DIR = 8,
    M1PWM = 9,
    M2PWM = 10,
    LED = 13;

//Variables
double rayon=1.75, toursM1=0, toursM2=0, freinage=6;
int tours, DIR1, DIR2, delai, vitesse, distance;

  //Fonctions pour le déplacement

  //Fonction de base
void deplacement(int vitesse,int DIR1,int DIR2,int distance) {
    //Valeurs max pour 3V estimer a 70 mais tests à faire encore
  if (vitesse>=130) vitesse = 130;
    //Valeur nécessairement positif puisque analogue (8 bit)
  if (vitesse<0) vitesse=-vitesse;
  // Direction et vitesse moteur 1
  tours=dis(distance);
  analogWrite(M1PWM,vitesse);
  digitalWrite(M1DIR,DIR1);
  // Direction et vitesse moteur 2
  analogWrite(M2PWM,vitesse);
  digitalWrite(M2DIR,DIR2);
    for (int toursMoyen=(toursM1+toursM2)/2;tours>toursMoyen;) {}
  toursM1=0;
  toursM2=0;
}
  //Fonction avancer
void avancer(int vitesse,int distance) {
  // Sens vers l'avant
  DIR1=HIGH;
  DIR2=HIGH;
  deplacement(vitesse,DIR1,DIR2,distance);
}
 //Fonction reculer
void reculer(int vitesse,int distance) {
  // Sens vers l'arrière
  DIR1=LOW;
  DIR2=LOW;
  deplacement(vitesse,DIR1,DIR2,distance);
}
  //Fonction rotation à droite
void rotationG(int vitesse,int distance) {
  // Sens mixe pour tourner vers la droite
  DIR1=HIGH;
  DIR2=LOW;
  deplacement(vitesse,DIR1,DIR2,distance);
}
  //Fonction rotation à gauche
void rotationD(int vitesse,int distance) {
  // Sens mixe pour tourner vers la gauche
  DIR1=LOW;
  DIR2=HIGH;
  deplacement(vitesse,DIR1,DIR2,distance);
}
  //Freiner
void brake(int delai) {
  DIR1=LOW;
  DIR2=LOW;
  vitesse=0;
  distance=0;
  deplacement(vitesse,DIR1,DIR2,distance);
}

// Fonction pour compter le nombre de tours
void count1() {
toursM1++;
 }
void count2() {
toursM2++;
 }

//Nombre de clics pour distance
int dis(int distance) {
tours=distance/rayon*16-freinage;
return tours;
}

void setup() {
  // put your setup code here, to run once:
pinMode(encoderPin1, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoderPin1), count1, FALLING);
pinMode(encoderPin2, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoderPin2), count2, FALLING);


}

void loop() {
  // put your main code here, to run repeatedly:
avancer(60,100);
}
