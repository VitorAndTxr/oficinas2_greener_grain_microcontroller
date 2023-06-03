#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#include <GPIO/GPIOInit.h>
#endif

//Definicao motor

const int delayPassosLento = 3000;
const int delayPassosRapidos = 2000;

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

void gira(int sentido, int passos, int delayPassos, Motor motor)
{
    if (sentido == 0){ 
      digitalWrite(motor.Dir, HIGH);
      Serial.println("Spinning Clockwise...");
      
      for(int i = 0; i<passos; i++)
      {
        digitalWrite(motor.Step, HIGH);
        delayMicroseconds(delayPassos);
        digitalWrite(motor.Step, LOW);
        delayMicroseconds(delayPassos);
      }
    }
    else if (sentido == 1){
      digitalWrite(DIR, LOW);
      Serial.println("Spinning Anti-Clockwise...");

      for(int i = 0; i<passos; i++)
      {
        digitalWrite(motor.Step, HIGH);
        delayMicroseconds(delayPassos);
        digitalWrite(motor.Step, LOW);
        delayMicroseconds(delayPassos);
      }
    }

}

struct Motor{
  int Step;
  int Dir;
};