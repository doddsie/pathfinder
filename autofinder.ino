#include <Servo.h>


const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;
const int IN4 = 7;
const int IN3 = 6;
const int ENB = 5;
const int ledPin = 13;



const int trigPin = 3;
const int echoPin = 2;
float microsecondsToFeet(float microseconds)
{
  return microseconds / 979 / 2;
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

Servo myservo;  // create servo object to control a servo


void setup()
{

    Serial.begin(9600);

  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, LOW);

  //delay is used to control the speed, the lower the faster.
  //reverse(step,delay);
  //reverse(80,20);
  //forward(step,delay);
  //forward(80,20);
    myservo.attach(4);  // attaches the servo on pin 9 to the servo object



}

static int i= 0;
static bool move = true;
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int pos = 0;    // variable to store the servo position

void loop()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  if (i++ %60== 0) {
    move = !move;
  }
if (move) {  
  Serial.println("loop 1");

  // IN1 = LEFT  BACKWARD
  // IN1 = LEFT FORWARD
  // IN3 - RIGHT FORWARD
  // IN4 = RIGHT backward

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 100);
} else {
  Serial.println("loop 0");

    digitalWrite(IN1, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN4, 0);
}

    
  long duration, inches;
  float feet;

   
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }


}
