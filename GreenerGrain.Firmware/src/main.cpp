#include <Arduino.h>

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-hc-sr04-ultrasonic-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

const int trigPinUS1 = 32;
const int echoPinUS1 = 39;

const int trigPinUS2 = 33;
const int echoPinUS2 = 34;

const int trigPinUS3 = 25;
const int echoPinUS3 = 35;

const int loadCellSck = 15;
const int loadCellDT =  2;

const int stepMotor1 = 12;
const int dirMotor1 = 14;

const int stepMotor2 = 27;
const int dirMotor2 = 26;


//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
void initiateUltrassonicSensor(void);
void measureDistanceUS(void);

void setup() {
  Serial.begin(921600);
  initiateUltrassonicSensor();
}

void loop() {
  measureDistanceUS();
  delay(1000);
}

void initiateUltrassonicSensor(){
    pinMode(trigPinUS1, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPinUS1, INPUT); // Sets the echoPin as an Input
    pinMode(trigPinUS2, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPinUS2, INPUT); // Sets the echoPin as an Input
    pinMode(trigPinUS3, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPinUS3, INPUT); // Sets the echoPin as an Input
}

void measureDistanceUS(){
  digitalWrite(trigPinUS1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinUS1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinUS1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinUS1, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm) US 1: ");
  Serial.println(distanceCm);

  digitalWrite(trigPinUS2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinUS2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinUS2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinUS2, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm) US 2: ");
  Serial.println(distanceCm);

  digitalWrite(trigPinUS3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinUS3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinUS3, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinUS3, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm) US 3: ");
  Serial.println(distanceCm);
}

