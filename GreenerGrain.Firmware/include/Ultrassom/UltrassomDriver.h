#include <Arduino.h>


const int trigPinUS1 = 32;
const int echoPinUS1 = 39;

const int trigPinUS2 = 23;//33
const int echoPinUS2 = 34;

const int trigPinUS3 = 25;
const int echoPinUS3 = 35;


//define sound speed in cm/uS

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

void initiateUltrassonicSensor(void);
void measureDistanceUS(void);

struct Sensor{
  int trig;
  int echo;
};

const Sensor UnitSensors[3] = {
  {
    trigPinUS1,
    echoPinUS1
  },
  {
    trigPinUS2,
    echoPinUS2
  },
  {
    trigPinUS3,
    echoPinUS3
  }
  };

void initiateUltrassonicSensor(){
    pinMode(UnitSensors[0].trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(UnitSensors[0].echo, INPUT); // Sets the echoPin as an Input
    pinMode(UnitSensors[1].trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(UnitSensors[1].echo, INPUT); // Sets the echoPin as an Input
    pinMode(UnitSensors[2].trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(UnitSensors[2].echo, INPUT); // Sets the echoPin as an Input
}

float measureDistanceUS(Sensor sensor){
  

  digitalWrite(sensor.trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(sensor.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor.trig, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(sensor.echo, HIGH);
  
  // Calculate the distance
  float distanceCm = duration * SOUND_SPEED/2;
  
  // Prints the distance in the Serial Monitor
  // Serial.print("Distance (cm): ");
  // Serial.println(distanceCm);

  return distanceCm;
}