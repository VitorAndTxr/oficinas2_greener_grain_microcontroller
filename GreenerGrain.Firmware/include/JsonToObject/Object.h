#include <ArduinoJson.h>

StaticJsonDocument<200> deserializeJson(uint8_t *data){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }
    return doc;
}