#include <Arduino.h>
#include<ESPAsyncWebServer.h>
#include<WiFi.h>

      
const char *wifi_network_ssid = "Inam ul Rehman";
const char *wifi_network_password = "in123456";                       // not necessary your laptop and esp32 should be connected to same network
    
const char *soft_ap_ssid = "ESP32 Soft AP";
const char *soft_ap_password = "";

AsyncWebServer server(80);

String json_packet;
int numberOfNetworks;

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


  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request){

      request->send(200, "text", "Hello i am working");

  });

  server.on("/" , HTTP_GET, [](AsyncWebServerRequest *request){



    json_packet += '{';
    json_packet += '\n';
    Serial.println("Scanning networks...");
    numberOfNetworks = WiFi.scanNetworks();
    Serial.println("Scan done");
    int rssi[numberOfNetworks];

    if(numberOfNetworks == 0)
    {
      Serial.println("No Networks Found");
    }
    else
    {
      Serial.print(numberOfNetworks);
      Serial.println(" networks found");
      for (int i = 0; i < numberOfNetworks; ++i)
      {
        json_packet += '"';
        json_packet += WiFi.SSID(i);
        json_packet += '"';
        json_packet += ':';
        json_packet += WiFi.RSSI(i);
        rssi[i] = WiFi.RSSI(i);
        json_packet += ',';
        json_packet += '\n';
      }
    }
    json_packet += '}';

    for(int j = 1;j < numberOfNetworks; ++j)
    {
      if(rssi[0] < rssi[j])
        rssi[0] = rssi[j];
    }
    json_packet+= String(rssi[0]);

    request->send(200,"application/json", json_packet);
  });
  
}    

void loop() {


  
}