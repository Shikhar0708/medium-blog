#include<WiFi.h>
#include<ESPAsyncWebServer.h>
#include<AsyncTCP.h>
#include<ESP.h>
#include <Preferences.h>

Preferences preferences;

AsyncWebServer server(80);
const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
void First_login(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("The MEDIUM","MEDIUMBLOG123");
  server.begin();
  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>&input2=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String inputMessage,inputMessage1;
  String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      if (request->hasParam(PARAM_INPUT_2)){
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      inputMessage1 = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
  preferences.putString("ssid", inputMessage); 
  preferences.putString("password", inputMessage1);

  Serial.println("Network Credentials Saved using Preferences");

  preferences.end();
    }
    }
else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println("");
    Serial.println(inputMessage);
    Serial.println(inputMessage1);
    request->send(200, "text/html", "200"
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
  
}

void setup() {
    Serial.begin(9600);
    preferences.begin("Medium-App", false); 
    String ssid = preferences.getString("ssid", ""); 
    String password = preferences.getString("password", "");
    if(ssid=="" || password==""){
      First_login();
      delay(60*1000);
      ESP.restart();
      } 
      else{
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(),password.c_str());
          while (WiFi.status() != WL_CONNECTED) {
                Serial.print('.');
                delay(1000);
  }
     Serial.println(WiFi.localIP());
        
      }

} 

void loop() {

}
