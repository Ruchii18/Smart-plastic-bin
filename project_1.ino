// OKWUCHI'S PROJECT 1 ( SMART PLASTIC BIN )
// WARNING : the threshold is highly dependent on the lightning in the environment
// so therefore check the serial monitor to adjust values 
# include <Servo.h>
Servo a;// plastic bin servo
int trig = 8;
int echo = 7;
int active_bz = 6; //active buzzer
int passive_bz = 5; //passive buzzer
int RED = 4;
int GREEN = 3;
int dist ;
float sign_time ;
int pht_sensor = A1;

void setup() {
  a.attach(12);
  a.write(0);// ensures that the servo starts from <0 when powered on
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(active_bz, OUTPUT);
  pinMode(passive_bz, OUTPUT); 
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
digitalWrite( trig, LOW);
delay(3);
digitalWrite( trig, HIGH);
delay(10);
digitalWrite( trig, LOW);
sign_time = pulseIn( echo, HIGH);// ⌚ it takes for the echo to recieve the signal ( in microseconds)
dist = (0.034 * sign_time)/2 ;// distance calculated to centimeters (Ultrasonic sound speed = 340m/s)
int pht=analogRead(pht_sensor);// threshold
Serial.print("distance in cm :");
Serial.println(dist);
Serial.print("threshold :");
Serial.println(pht);
// if the bin reads a plastic 
if( dist >3 && dist <= 15 &&  pht >= 63){
  tone(passive_bz, 440); //A4 sound
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
  a.write(0);
  delay(400);

  tone(passive_bz, 587); //D4 sound   
  a.write(70);   // lid opens
  delay(1000);

  noTone(passive_bz); // remains open
  delay(2500);
  
  digitalWrite(GREEN, LOW);  // closes and green light goes off
  a.write(0);
  delay(500);

  delay(2000); // rests
  }
// not a plastic!!!
else if ((dist >4 && dist <= 16) && (pht < 45)){
  //based of my hypothesis ( highly dependent on temperature)
  for(int i=0; i<3; i++){ // 3 short beeps
    digitalWrite(active_bz, HIGH);
    digitalWrite(RED, HIGH);
    delay(500/3);
    digitalWrite(active_bz, LOW);
    digitalWrite(RED, LOW);
    delay(150);
  }
  delay(1500);
} 
else {
  noTone(passive_bz);
  digitalWrite(active_bz, LOW);
  digitalWrite( RED, LOW);  // nothing basically happens
  digitalWrite(GREEN, LOW);
}} // AGAIN😒, this depends on room lightning, so check the serial monitor and adjust your results



