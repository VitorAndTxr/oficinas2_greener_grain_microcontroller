#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#include <Arduino.h>

#endif

const int stepMotor1 = 12;
const int dirMotor1 = 14;

const int stepMotor2 = 27;
const int dirMotor2 = 26;

enum SpinDirection {HORARIO, ANTIHORARIO};

//Definicao motor

const int delayPassosLento = 3000;
const int delayPassosRapidos = 2000;

struct Motor{
  int Step;
  int Dir;
};

const Motor UnitMotors[2] = {{
  stepMotor1,
  dirMotor1
},
{
  stepMotor2,
  dirMotor2
}};

void setupMotor()
{
  pinMode(UnitMotors[0].Step, OUTPUT);
  pinMode(UnitMotors[0].Dir, OUTPUT);
  pinMode(UnitMotors[1].Step, OUTPUT);
  pinMode(UnitMotors[1].Dir, OUTPUT);
}

void gira(SpinDirection sentido, int passos, int delayPassos, Motor motor)
{
    if (sentido == HORARIO){ 
      digitalWrite(motor.Dir, HIGH);
      
      for(int i = 0; i<passos; i++)
      {
        digitalWrite(motor.Step, HIGH);
        delayMicroseconds(delayPassos);
        digitalWrite(motor.Step, LOW);
        delayMicroseconds(delayPassos);
      }
    }
    else if (sentido == ANTIHORARIO){
      digitalWrite(motor.Dir, LOW);

      for(int i = 0; i<passos; i++)
      {
        digitalWrite(motor.Step, HIGH);
        delayMicroseconds(delayPassos);
        digitalWrite(motor.Step, LOW);
        delayMicroseconds(delayPassos);
      }
    }

}

