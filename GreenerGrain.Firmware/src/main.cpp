#include "WifiServer/WifiConfig.h"
#include "HttpServer/Server.h"
#include "HttpClient/HttpClientConfig.h"

void setup() {
  Serial.begin(115200);
  initiateWifi();
  initiateServer();
  //initiateUltrassonicSensor();
}

void loop() {
  Serial.println("Oi!");
  getAPIHealth();
  delay(5000);
}





