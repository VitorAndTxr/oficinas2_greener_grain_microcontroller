#include <WiFi.h>

const char* ssid = "Vitor2.4G";
const char* password = "eunaosei";

void initiateWifi(){
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
}