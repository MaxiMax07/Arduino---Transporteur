  // Nom pour les pin directionnel du motorshield
const unsigned char AIN1 = 7;
const unsigned char BIN1 = 8;
const unsigned char AIN2 = 9;
const unsigned char BIN2 = 10;
const unsigned char LED = 13;
  // Déclaration des variables
int vitesse;
int delai;
int DIR1;
int DIR2;


void setup() {
  // put your setup code here, to run once:

  //On setup toute les pins directionnelles et le LED
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Cela sert à ramasser en continue les valeurs des capteurs

  // Par exemple, le led jaune de base va s'allumer seulement
  // lorsque le robot fait une rotation ou est à l'arrêt

   if (DIR1==HIGH && DIR2==LOW) {
      digitalWrite(LED, HIGH); }
   else if (DIR1==LOW && DIR2==HIGH) {
      digitalWrite(LED, HIGH); }
   else {
      digitalWrite(LED, LOW); }
}

  //Fonctions pour le déplacement

  //Fonction avancer
void avancer(int vitesse,int delai) {
  //Valeurs max pour 3V estimer a 70 mais tests à faire encore
      if (vitesse>=70) vitesse = 70;
   digitalWrite(AIN1,1);
   digitalWrite(BIN1,1);
   analogWrite(AIN2,vitesse);
   analogWrite(BIN2,vitesse);
   delay(delai);
}
 //Fonction reculer
void reculer(int vitesse,int delai) {
      //Vitesse doit toujours être positive
  if (vitesse<0) vitesse=-vitesse;
      //Valeurs max pour 3V estimer a 70 mais tests à faire encore
  if (vitesse>=70) vitesse = 70;
   digitalWrite(AIN2,1);
   digitalWrite(BIN2,1);
   analogWrite(AIN1,vitesse);
   analogWrite(BIN1,vitesse);
   delay(delai);
}
  //Fonction rotation à droite
void rotationD(int vitesse, int delai) {
      //Valeurs max pour 3V estimer a 70 mais tests à faire encore
   if (vitesse>=70) vitesse = 70;
   digitalWrite(AIN1,1);
   digitalWrite(BIN2,1);
   analogWrite(AIN2,vitesse);
   analogWrite(BIN1,vitesse);
   delay(delai);
}
  //Fonction rotation à gauche
void rotationG(int vitesse, int delai) {
     //Valeurs max pour 3V estimer a 70 mais tests à faire encore
   if (vitesse>=70) vitesse = 70;
   digitalWrite(BIN1,1);
   digitalWrite(AIN2,1);
   analogWrite(BIN2,vitesse);
   analogWrite(AIN1,vitesse);
   delay(delai);
}
  //Freiner
void brake(int delai) {
   digitalWrite(AIN1,1);
   digitalWrite(BIN2,1);
   analogWrite(AIN2,1);
   analogWrite(BIN1,1);
   delay(delai);
}
  //Coast, frein brutal
void arret(int delai) {
   digitalWrite(AIN1,0);
   digitalWrite(BIN2,0);
   analogWrite(AIN2,0);
   analogWrite(BIN1,0);
   delay(delai);
}


    // Ici on écrit le code! Avec les fonctions avancer, reculer
    // brake, rotationD et rotationG sous la forme (vitesse,delai)
    // vitesse étant compris entre 0 et 255 (8bit)
    // delai étant en ms
