#include <ESPAsyncWebServer.h>
#include <assert.h>
#include "JsonToObject/Object.h"
#include "Motor/MotorFirmware.h"




void handleRequest(AsyncWebServerRequest * request,uint8_t *data);
AsyncWebServer server(80);
 
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

    StaticJsonDocument<200> doc = deserializeJson(data);

    int peso = doc["peso"];
    int module = doc["module"];
    
    gira(ANTIHORARIO, 400, delayPassosRapidos,UnitMotors[module]);



    request->send(200);
}