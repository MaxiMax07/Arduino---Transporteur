int rawsensorValue = 0; // variable to store the value coming from the sensor
int sensorcount0 = 0;
int sensorcount1 = 0;
long count = 0;
void setup() {
 int i;
 for(i=5;i<=8;i++)
 pinMode(i, OUTPUT);
 Serial.begin(9600);
 int leftspeed = 255; //255 is maximum speed
 int rightspeed = 255;
}
void loop() {
 rawsensorValue = analogRead(0);
 if (rawsensorValue < 600){ //Min value is 400 and max value is 800, so state chance can be done at 600.
 sensorcount1 = 1;
 }
 else {
 sensorcount1 = 0;
 }
 if (sensorcount1 != sensorcount0){
 count ++;
 }
 sensorcount0 = sensorcount1;
 Serial.println(count);
}
