
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor
const int ratioPeq = 15;
const int ratioGde = 96;
// 1/3 vuelta = 4369 pasos = 8 segundos
const int pasos_por_it = 100;

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
int buffer_pasos = 0;

void setup() {
  Serial.begin(300);
  myStepper.setSpeed(15);
  pinMode(LED, OUTPUT);
  pinMode(hall1, INPUT);
  pinMode(hall2, INPUT);
  pinMode(hall3, INPUT);
}

void loop() {
  if (abs(buffer_pasos)>pasos_por_it){
    if (buffer_pasos>0){
      myStepper.step(pasos_por_it);
      buffer_pasos = buffer_pasos - pasos_por_it;
    } else {
      myStepper.step(-pasos_por_it);
      buffer_pasos = buffer_pasos + pasos_por_it;
    }
    digitalWrite(LED, LOW);
  }
  
  valor1 = analogRead(hall1);
  valor2 = analogRead(hall2);
  valor3 = analogRead(hall3);
  if (valor1 > 600){
    current_position = 1;
    digitalWrite(LED, HIGH);
  } else if (valor2 > 600){
    current_position = 2;
    digitalWrite(LED, HIGH);
  } else if (valor3 > 600){
    current_position = 3;
    digitalWrite(LED, HIGH);
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
    buffer_pasos = buffer_pasos + steps;
  }
}
