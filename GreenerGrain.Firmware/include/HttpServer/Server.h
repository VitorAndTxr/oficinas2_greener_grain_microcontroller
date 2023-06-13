#include <ESPAsyncWebServer.h>
#include <assert.h>
#include "JsonToObject/Object.h"

void handleRequest(AsyncWebServerRequest * request,uint8_t *data);
AsyncWebServer server(80);
 
void testMotor(int module);

void initiateServer() { 

  server.on(
    "/requestGrain",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      
    handleRequest(request, data); 
  });
 
  server.begin();
}

void handleRequest(AsyncWebServerRequest * request,uint8_t *data){

    if(CurrentState == WORKINKG ){
      request->send(503,"application/json","{\"message\":\"A unidade selecionada nao está disponível\"}");
      return;
    }

    StaticJsonDocument<200> doc = deserializeJson(data);

    int peso = doc["peso"];
    int module = doc["module"];
    
    Order = {
      module,
      peso,
    };

    CurrentState = WORKINKG;

    request->send(200);
}

