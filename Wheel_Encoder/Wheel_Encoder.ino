//Encoder pins doivent être 2 ou 3 car c'est les seules compatibles avec attachInterrupt
#define encoderPin1 2
#define encoderPin2 3

//Variables
volatile int toursM1=0, toursM2, tours=0;

// Fonction pour compter le nombre de tours
void count1() {
tours=tours+1;
Serial.print(tours);
 }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Initialisation du test:");
pinMode(encoderPin2, INPUT);
attachInterrupt(digitalPinToInterrupt(encoderPin2), count1, FALLING);

}

void loop() {

if (tours!=toursM1) {
  toursM1=tours;
Serial.print("Tours:");
Serial.println(toursM1);}
}
