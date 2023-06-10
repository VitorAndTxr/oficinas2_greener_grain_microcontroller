#include "Ultrassom/UltrassomDriver.h"
#include "LoadCell/LoadCellFirmware.h"
#include "Motor/MotorFirmware.h"
#include "ModuleTasks.h"
#include "WifiServer/WifiConfig.h"
#include "HttpServer/Server.h"
#include "HttpClient/HttpClientConfig.h"



void inicializationMode(void);
void testComponents(void);
void medirPeso(void);

void setup() {


  Serial.begin(115200);

  initiateWifi();
  initiateServer();
  setupMotor();
  initiateUltrassonicSensor();
  setupLoadCell();
  inicializationMode();
  CurrentState = IDLE;
}



void loop() {

  if(Order.module>-1)
  {
    HandleDispenseOrder();
  }
  if (Serial.available() > 0) {

    char inByte = Serial.read();

    if(inByte == 't')
      testComponents();

    if(inByte == 'p')
      medirPeso();

  }
}

void medirPeso(){
int flag = 1;
  do{

    Serial.print("Valor balança: ");

    float curretPeso = getCurrentWeight();
    Serial.print(curretPeso);
    Serial.println("g");

    delay(200);
    if (Serial.available() > 0) {

      char inByte = Serial.read();

      if(inByte == 's')
        flag = 0;

    }



  }while(flag == 1);
  
}

void testComponents(){

  Serial.print("Sensor módulo 1:");
  Serial.println(measureDistanceUS(UnitSensors[0]));
  Serial.print("Sensor módulo 2:");
  Serial.println(measureDistanceUS(UnitSensors[1]));
  Serial.print("Sensor Balança:");
  Serial.println(measureDistanceUS(UnitSensors[2]));

  Serial.println("Teste motor módulo 1");

  gira(HORARIO, 100, delayPassosLentos, UnitMotors[0]);
  gira(ANTIHORARIO, 100, delayPassosLentos, UnitMotors[0]);

  Serial.println("Teste motor módulo 2");

  gira(HORARIO, 100, delayPassosLentos, UnitMotors[1]);
  gira(ANTIHORARIO, 100, delayPassosLentos, UnitMotors[1]);





}

void inicializationMode(){
  hw_timer_t *My_timer = timerBegin(0, 80, true);
  int time = 0;

  Serial.println("Envie uma das opções abaixo ou aguarde a inicialização");

  Serial.println("'t' - Renove a tara");
  Serial.println("'p' - Pular inicialização");


  while(time <15000){

    time = timerReadMilis(My_timer);

    if (Serial.available() > 0) {

      char inByte = Serial.read();

      if(inByte == 't')
        calibrateLoadCell();
      if(inByte == 'p')
        break;

    }
    Serial.print(".");
    delay(500);
  }
}





