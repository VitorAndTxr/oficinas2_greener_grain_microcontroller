#include "Ultrassom/UltrassomDriver.h"
#include "LoadCell/LoadCellFirmware.h"
#include "Motor/MotorFirmware.h"
#include "WifiServer/WifiConfig.h"
#include "HttpServer/Server.h"
#include "HttpClient/HttpClientConfig.h"
#include "esp_task_wdt.h"


void inicializationMode(void);

void setup() {


  Serial.begin(115200);
  esp_task_wdt_deinit();

  initiateWifi();
  initiateServer();
  setupMotor();
  initiateUltrassonicSensor();
  setupLoadCell();
  inicializationMode();
}

void testMotor(){


    //StaticJsonDocument<200> doc = deserializeJson(data);

    //int peso = doc["peso"];
    //int module = doc["module"];
    
    float balanceDistance = measureDistanceUS(UnitSensors[2]);
    float curretPeso = getCurrentWeight();

    Serial.println("Esperando recipiente");

    do{
          balanceDistance = measureDistanceUS(UnitSensors[2]);
          curretPeso = getCurrentWeight();
          delay(100);



    }while(((balanceDistance > 25) || (curretPeso<15)));

    Serial.println("Aguardando tara...");

    delay(5000);


    gira(ANTIHORARIO, 400, delayPassosRapidos,UnitMotors[currentModule]);
    currentModule = -1;
}

void loop() {

  if(currentModule>-1)
    testMotor();
  //getAPIHealth();

  // Serial.println("Init");

  // Serial.println(measureDistanceUS(UnitSensors[0]));
  // Serial.println(measureDistanceUS(UnitSensors[1]));
  // Serial.println(measureDistanceUS(UnitSensors[2]));

  
  // gira(1, 100, delayPassosLento, UnitMotors[0]);
  // delay(1000);
  // gira(0, 100, delayPassosLento, UnitMotors[0]);
  // delay(1000);
  // gira(1, 100, delayPassosLento, UnitMotors[1]);
  // delay(1000);
  // gira(0, 100, delayPassosLento, UnitMotors[1]);

  //Serial.println(getCurrentWeight());
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





