#include <PID_AutoTune_v0.h>

#include <PID_v1.h>

//Déclaration des variables
double Setpoint, Input, Output;

//Paramètres de callibration
double Kp=2, Ki=5, Kd=1;
//Les liens
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  // put your setup code here, to run once:

  
myPID.SetOutputLimits(0,150);  //Vitesses limite du PID
myPID.SetSampleTime(100); //permet de choisir la vitesse d'actualisation du PID
myPID.SetMode(AUTOMATIC); //PID is in AUTOMATIC or MANUAL
}

void loop() {
  // put your main code here, to run repeatedly:

myPID.Compute(); //permet de lancer l'algorythme
/*myPID.SetTunings(Kp,Ki,Kd) permet de changer les variables par défaut
myPID.SetControllerDirection() permet de changer le sens du PID, DIRECT (redessendre vitesse) ou REVERSE
GetKp()
GetKi()
GetKd()
GetMode()
myPID.GetDirection()*/

}
