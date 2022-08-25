// #include <Arduino.h>
#include<ESPAsyncWebServer.h>
#include<WiFi.h>

      
const char *wifi_network_ssid = "Inam ul Rehman";
const char *wifi_network_password = "in123456";                       // not necessary your laptop and esp32 should be connected to same network
    
const char *soft_ap_ssid = "ESP32 Soft AP";
const char *soft_ap_password = "";

AsyncWebServer server(80);

void setup() {

  Serial.begin(9600);

  WiFi.mode(WIFI_MODE_APSTA);
  // WiFi.mode(WIFI_AP_STA);

  WiFi.softAP(soft_ap_ssid,soft_ap_password);
  Serial.println("Connecting esp32 to the WiFi...");
  WiFi.begin(wifi_network_ssid,wifi_network_password);

  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print("<");
      delay(100);
      Serial.println("<connecting>");
  }
  Serial.println("Connected to WiFi NetWork.");

  Serial.print("ESP32 Soft AP Ip: ");
  Serial.println(WiFi.softAPIP());

  Serial.print("ESp32 IP on WiFi Network: ");
  Serial.println(WiFi.localIP());


  server.begin();


  server.on("/", HTTP_GET , [](AsyncWebServerRequest *request){

      request->send(200, "text", "Hello i am working");

  });
  
}    

void loop() {
  
}