  // Nom pour les pin directionnel du motorshield
const unsigned char M1DIR = 7;
const unsigned char M2DIR = 8;
const unsigned char M1PWM = 9;
const unsigned char M2PWM = 10;
const unsigned char LED   = 13;

  // Déclarations des constantes d'états
const int ARRETER       = 0;
const int AVANCER       = 1;
const int TOURNERGAUCHE = 2;
const int RECULER       = 3;
const int TOURNERDROITE = 4;


void setup() {
    //On initialise toute les pins directionnelles et le LED
  Serial.begin(9600);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M1DIR, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
    // Cela sert à ramasser en continue les valeurs des capteurs

  int action = ARRETER;
    // Par exemple, le led jaune de base va s'allumer seulement
    // lorsque le robot fait une rotation ou est à l'arrêt
  if (action == TOURNERGAUCHE || action == TOURNERDROITE || action == ARRETER) {
    digitalWrite(LED, HIGH); 
  }
  else {
    digitalWrite(LED, LOW); 
  }
    //n'oublie pas, arduino ne fait qu'une action à la fois 
}

//Fonctions pour le déplacement

  //Fonction de base
void deplacement(int vitesse,int action,int duree) {
  int dir1 = HIGH;
  int dir2 = HIGH;

    //Restreindre la valeur max en analogue
  if (vitesse >= 255) {
    vitesse = 255;
  }
    //Valeur négative inverse l'action
  if (vitesse < 0 && vitesse >= -255) {
    vitesse = -vitesse;
    action = (action + 2) % 4; //inverse l'action
  } 
  if (action == ARRETER) {
    vitesse = 0;
  }

  switch(action) {
    case AVANCER:
      dir1 = HIGH;
      dir2 = HIGH;
      break;
    case RECULER:
      dir1 = LOW;
      dir2 = LOW;
      break;
    case TOURNERDROITE:
      dir1 = HIGH;
      dir2 = LOW;
      break;
    case TOURNERGAUCHE:
      dir1 = LOW;
      dir2 = HIGH;
      break;
  }
  activerMoteur(vitesse, dir1, dir2);

    // Temps de la procédure
  delay(duree);
}


void activerMoteur(int vitesse, int dir1, int dir2) {
    // action et vitesse moteur 1
  analogWrite(M1PWM,vitesse);
  digitalWrite(M1DIR,dir1);
  
    // action et vitesse moteur 2
  analogWrite(M2PWM,vitesse);
  digitalWrite(M2DIR,dir2);
}

    // Ici on écrit le code! 
    // vitesse étant compris entre 0 et 255 (8bit)
    // delai étant en ms
