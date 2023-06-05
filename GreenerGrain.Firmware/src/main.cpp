#include "WifiServer/WifiConfig.h"
#include "HttpServer/Server.h"
#include "HttpClient/HttpClientConfig.h"
#include "Ultrassom/UltrassomDriver.h"
#include "LoadCell/LoadCellFirmware.h"


void inicializationMode(void);

void setup() {


  Serial.begin(115200);
  initiateWifi();
  initiateServer();
  setupMotor();
  initiateUltrassonicSensor();
  setupLoadCell();
  inicializationMode();
}

void loop() {
  //getAPIHealth();

  // measureDistanceUS(UnitSensors[0]);
  // measureDistanceUS(UnitSensors[1]);
  // measureDistanceUS(UnitSensors[2]);

  
  // gira(1, 100, delayPassosLento, UnitMotors[0]);
  // delay(1000);
  // gira(0, 100, delayPassosLento, UnitMotors[0]);
  // delay(1000);
  // gira(1, 100, delayPassosLento, UnitMotors[1]);
  // delay(1000);
  // gira(0, 100, delayPassosLento, UnitMotors[1]);
  // delay(1000);

  //getValue();
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
      
      Serial.print(".");

    }
    delay(500);
  }
}





