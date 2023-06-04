#include "WifiServer/WifiConfig.h"
#include "HttpServer/Server.h"
#include "HttpClient/HttpClientConfig.h"
#include "Motor/MotorFirmware.h"
#include "Ultrassom/UltrassomDriver.h"



void setup() {
  Serial.begin(115200);
  initiateWifi();
  initiateServer();
  setupMotor();
  initiateUltrassonicSensor();
}

void loop() {
  Serial.println("Oi!");
  //getAPIHealth();

  measureDistanceUS(UnitSensors[0]);
  measureDistanceUS(UnitSensors[1]);
  measureDistanceUS(UnitSensors[2]);

  
  gira(1, 100, delayPassosLento, UnitMotors[0]);
  delay(1000);
  gira(0, 100, delayPassosLento, UnitMotors[0]);
  delay(1000);
  gira(1, 100, delayPassosLento, UnitMotors[1]);
  delay(1000);
  gira(0, 100, delayPassosLento, UnitMotors[1]);
  delay(1000);
}





