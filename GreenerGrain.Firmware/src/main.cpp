#include "Ultrassom/UltrassomDriver.h"
#include "LoadCell/LoadCellFirmware.h"
#include "Motor/MotorFirmware.h"
#include "ModuleTasks.h"
#include "WifiServer/WifiConfig.h"
#include "HttpServer/Server.h"
#include "HttpClient/HttpClientConfig.h"


void inicializationMode(void);
void testComponents(void);
void medirPeso(void);
void sendUnityStatus();

//String serverName = "http://192.168.18.66:6006/api/v1";
void setup(){


  Serial.begin(115200);

  initiateWifi();
  initiateServer();
  //setupMotor();
  //initiateUltrassonicSensor();
  //setupLoadCell();
  //inicializationMode();
  CurrentState = IDLE;
}



void loop() {

  sendUnityStatus();

  delay(5000);
  /*if(Order.module>-1)
  {
    HandleDispenseOrder();
  }
  if (Serial.available() > 0) {

    char inByte = Serial.read();

    if(inByte == 't')
      testComponents();

    if(inByte == 'p')
      medirPeso();

  }*/
}



void medirPeso(){
int flag = 1;
  do{

    Serial.print("Valor balança: ");

    float curretPeso = getCurrentWeight();
    Serial.print(curretPeso);
    Serial.println("g");

    delay(200);
    if (Serial.available() > 0) {

      char inByte = Serial.read();

      if(inByte == 's')
        flag = 0;
    }
  }while(flag == 1);
  
}

void testComponents(){

  Serial.print("Sensor módulo 1:");
  Serial.println(measureDistanceUS(UnitSensors[0]));
  Serial.print("Sensor módulo 2:");
  Serial.println(measureDistanceUS(UnitSensors[1]));
  Serial.print("Sensor Balança:");
  Serial.println(measureDistanceUS(UnitSensors[2]));



  Serial.println("Teste motor módulo 1");

  gira(HORARIO, 100, delayPassosLentos, UnitMotors[0]);
  gira(ANTIHORARIO, 100, delayPassosLentos, UnitMotors[0]);

  Serial.println("Teste motor módulo 2");

  gira(HORARIO, 100, delayPassosLentos, UnitMotors[1]);
  gira(ANTIHORARIO, 100, delayPassosLentos, UnitMotors[1]);
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

    }
    Serial.print(".");
    delay(500);
  }
}

// #include <WiFi.h>
// #include <HTTPClient.h>

// const char* ssid = "Vitor2.4G";
// const char* password = "eunaosei";

// //Your Domain name with URL path or IP address with path
// String serverName = "http://192.168.18.66:6006/api/v1";



// hw_timer_t * timer = NULL;

// int counter = 1;
// void IRAM_ATTR cb_timer(){
//     counter = !counter;
//    digitalWrite(2, counter);
// }

// void startTimer(){
//     //inicialização do timer. Parametros:
//     /* 0 - seleção do timer a ser usado, de 0 a 3.
//       80 - prescaler. O clock principal do ESP32 é 80MHz. Dividimos por 80 para ter 1us por tick.
//     true - true para contador progressivo, false para regressivo
//     */
//     timer = timerBegin(0, 80, true);

//     /*conecta à interrupção do timer
//      - timer é a instância do hw_timer
//      - endereço da função a ser chamada pelo timer
//      - edge=true gera uma interrupção
//     */
//     timerAttachInterrupt(timer, &cb_timer, true);

//     /* - o timer instanciado no inicio
//        - o valor em us para 1s
//        - auto-reload. true para repetir o alarme
//     */
//     timerAlarmWrite(timer, 1000000, true); 

//     //ativa o alarme
//     timerAlarmEnable(timer);
// }

// void stopTimer(){
//     timerEnd(timer);
//     timer = NULL; 
// }

// void setup(){
//     Serial.begin(115200);
//     //pinMode(2, OUTPUT);
//     //startTimer();
//     WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());
 
//   Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
// }

// void loop(){
  
//     //Check WiFi connection status
//     if(WiFi.status()== WL_CONNECTED){
//       HTTPClient http;

//       String serverPath = serverName + "/Health/Encrypt";
      
//       // Your Domain name with URL path or IP address with path
//       http.begin(serverPath.c_str());
      
//       // If you need Node-RED/server authentication, insert user and password below
//       //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
//       // Send HTTP GET request
//       http.addHeader("Content-Type", "application/json");
//       int httpResponseCode = http.POST("\"misael\"");
      
//       if (httpResponseCode>0) {
//         Serial.print("HTTP Response code: ");
//         Serial.println(httpResponseCode);
//         String payload = http.getString();
//         Serial.println(payload);
//       }
//       else {
//         Serial.print("Error code: ");
//         Serial.println(httpResponseCode);
//       }
//       // Free resources
//       http.end();
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     delay(5000);
// }



void sendUnityStatus(){
  HTTPClient http;

  http.begin(serverName +"/Unit/Alive");

  http.addHeader("Content-Type", "application/json");

  char texto[] = "\"misael\"";
  StaticJsonDocument<100> data;
  data["id"] = "F37D7922-8DA4-4406-B904-8CAD037B58F1";
  data["ip"] = WiFi.localIP().toString();
  	
  char buffer[100];
  serializeJson(data, buffer);

  Serial.println(buffer);

  int httpResponseCode = http.POST(buffer);

  String payload = "{}";

  if (httpResponseCode>0) {
     Serial.print("HTTP Response code: ");
     Serial.println(httpResponseCode);
    payload = http.getString();
     Serial.println("payload");

     Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  Serial.println("passa do end");

  //return "payload";

}





