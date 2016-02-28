//Encoder pins doivent être 2 ou 3 car c'est les seules compatibles avec attachInterrupt
double encoderPin1 = 2, encoderPin2=3,
    M1DIR = 7,
    M2DIR = 8,
    M1PWM = 9,
    M2PWM = 10,
    LED = 13;

//Variables
double rayon=1.75;
volatile int toursM1, toursM2;
int tours;

// Fonction pour compter le nombre de tours
void count1() {
toursM1++;
Serial.print("Tours:");
Serial.println(toursM1);
 }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  Serial.print("Initialisation du test:");
pinMode(encoderPin1, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoderPin1), count1, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
delay(3000);
digitalWrite(13,LOW);
delay(2000);
}
