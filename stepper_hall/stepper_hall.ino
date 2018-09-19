
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor
const int ratioPeq = 15;
const int ratioGde = 96;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// defines pins numbers

int LED = 13; // Use the onboard Uno LED
int hall1 = 1;  // 0°
int hall2 = 2;  // 120°
int hall3 = 3;  // 240°

// defines variables
int previous_position = 0;
int current_position = 0;
int valor1;
int valor2;
int valor3;
int signo;
int steps = 0;

void setup() {
  Serial.begin(300);
  myStepper.setSpeed(15);
  pinMode(LED, OUTPUT);
  pinMode(hall1, INPUT);
  pinMode(hall2, INPUT);
  pinMode(hall3, INPUT);
}

void loop() {
  valor1 = analogRead(hall1);
  valor2 = analogRead(hall2);
  valor3 = analogRead(hall3);
  if (valor1 > 600){
    current_position = 1;
  } else if (valor2 > 600){
    current_position = 2;
  } else if (valor3 > 600){
    current_position = 3;
  }
  if (previous_position==0){
    previous_position = current_position;
  } else {
    signo = current_position-previous_position;
    if (abs(signo)>1){
      signo = signo/-2;
    }
    steps = signo*stepsPerRevolution/3*(ratioGde/ratioPeq);
    previous_position = current_position;
    myStepper.step(steps);
  }
}
