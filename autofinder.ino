#include <Servo.h>

const int echoPin = 2;
const int trigPin = 3;
const int ENB = 5;
const int IN3 = 6;
const int IN4 = 7;
const int IN2 = 8;
const int IN1 = 9;
const int ENA = 10;
const int ledPin = 13;

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

class DistanceServo: public Servo 
{
public:
   void setpos(int pos);
   long  get_distance();
};

void DistanceServo::setpos(int pos) {
  write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);  
}

long DistanceServo::get_distance() {
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  return microsecondsToInches(pulseIn(echoPin, HIGH));
}

class Car {
    // IN1 = LEFT  BACKWARD
    // IN2 = LEFT FORWARD
    // IN3 - RIGHT FORWARD
    // IN4 = RIGHT backward
public:    
  void forward() {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  }
   
  void backward() {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  }

  void left() {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  }

  void right() {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  }
};


DistanceServo servo;  // create servo object to control a servo
Car           car;

void setup()
{
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  servo.attach(4);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  long distance = 0; 
  servo.setpos(90);
  distance = servo.get_distance();

  if (distance < 3) {
    car.right();
  } else {
    car.forward();
  } 
  delay(500);
}
