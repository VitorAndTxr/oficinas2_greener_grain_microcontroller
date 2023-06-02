#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include <assert.h>
 
const char* ssid = "Vitor2.4G";
const char* password =  "eunaosei";
 
AsyncWebServer server(80);
 
void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  server.on(
    "/post",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
 
      for (size_t i = 0; i < len; i++) {
        Serial.write(data[i]);
      }
 
      Serial.println();

      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, data);

      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      int peso = doc["peso"];
      int module = doc["module"];
      
      Serial.print("peso:");
      Serial.println(peso);
      Serial.print("module:");
      Serial.println(module);
 
      request->send(200);
  });
 
  server.begin();
}
 
void loop() {}