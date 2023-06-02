#include <Arduino.h>
#include "GPIO/GPIOInit.h"

//define sound speed in cm/uS

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
void initiateUltrassonicSensor(void);
void measureDistanceUS(void);

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