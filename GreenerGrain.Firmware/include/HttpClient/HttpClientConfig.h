#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.43.211:6006/api/v1/health";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String apiResponse;
String httpGETRequest(const char* serverName);


void getAPIHealth() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      apiResponse = httpGETRequest(serverName);

      Serial.println("apiResponse:");
      Serial.println(apiResponse);



      uint8_t *apiResponsePointer = reinterpret_cast<uint8_t*>(apiResponse.begin());
      StaticJsonDocument<200> apiResponseJson = deserializeJson(apiResponsePointer);

      boolean success = apiResponseJson["success"];
      String result = apiResponseJson["result"].as<String>();
      String errors = apiResponseJson["errors"].as<String>();


      Serial.println("success:");
      Serial.println(success);
      Serial.println("result:");
      Serial.println(result);
      Serial.println("errors:");
      Serial.println(errors);

      uint8_t *apiResultPointer = reinterpret_cast<uint8_t*>(result.begin());

      StaticJsonDocument<200> apiResultJson = deserializeJson(apiResultPointer);


      String message = apiResultJson["message"];
      int code = apiResultJson["code"];
      Serial.println("message:");
      Serial.println(message);
      Serial.println("code:");
      Serial.println(code);

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  
  if (httpResponseCode>0) {
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpResponseCode);
    payload = http.getString();
    // Serial.println("payload");

    // Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();


  return payload;
}