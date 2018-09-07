
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;         // number of steps the motor has taken

// defines pins numbers
const int trigPin = 13;
const int echoPin = 12;

// defines variables
long duration;
int distance;

void setup() {
  // initialize the serial port:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myStepper.setSpeed(15);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;
  // myStepper.step(1);
  int motorSpeed = map(distance, 0, 30, 15, 1);
  if(motorSpeed <1){
    motorSpeed = 1;
  }
  myStepper.setSpeed(motorSpeed);
  myStepper.step(stepsPerRevolution/32);

}
