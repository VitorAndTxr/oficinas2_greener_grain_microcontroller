#include <ESPAsyncWebServer.h>
#include <assert.h>
#include "JsonToObject/Object.h"

int currentModule = -1;

void handleRequest(AsyncWebServerRequest * request,uint8_t *data);
AsyncWebServer server(80);
 
void testMotor(int module);

void initiateServer() { 

  server.on(
    "/test-module",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      
    handleRequest(request, data); 
  });
 
  server.begin();
}

void handleRequest(AsyncWebServerRequest * request,uint8_t *data){

    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    // Serial.println();

    request->send(200);
    StaticJsonDocument<200> doc = deserializeJson(data);

    int peso = doc["peso"];
    int module = doc["module"];

    currentModule = module;
    
    // float balanceDistance = measureDistanceUS(UnitSensors[2]);
    // float curretPeso = getCurrentWeight();

    // Serial.println("Esperando recipiente");

    // do{
    //       balanceDistance = measureDistanceUS(UnitSensors[2]);
    //       curretPeso = getCurrentWeight();
    //       delay(400);



    // }while(((balanceDistance > 25) || (curretPeso<15)));

    // Serial.println("Aguardando tara...");

    // delay(5000);


    // gira(ANTIHORARIO, 400, delayPassosRapidos,UnitMotors[module]);

}

