  // Nom pour les pin directionnel du motorshield
double encoderPin1=2,
encoderPin2=3,
M1DIR = 7,
M2DIR = 8,
M1PWM = 9,
M2PWM = 10,
LED = 13;

  // Déclaration des variables
int vitesse, DIR1, DIR2, delai, tours, toursM1, toursM2, distance;

  // Déclaration des constantes liées aux composantes
double rayon=1.75, freinage=6; //(Distance en clics)  

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
toursM1=0; toursM2=0;
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

// Fonction pour compter le nombre de tours -- ISR
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
  Serial.begin(9600);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M1DIR, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(encoderPin1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin1), count1, CHANGE);
  pinMode(encoderPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin2), count2, CHANGE);

//Code définitif ici, qui ne recommence pas à l'infini

}

void loop() {

  // Code à tester ici!
Serial.print("Tours M1:");
Serial.println(toursM1);
Serial.print("Tours M2:");
Serial.println(toursM2);
delay(5000);

}
