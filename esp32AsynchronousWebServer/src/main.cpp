#include<Arduino.h>
#include<WiFi.h>
#include <ESPAsyncWebServer.h>

    const char *ssid = "ESP32";
    const char *password = "12345678";

    // IPAddress local_ip(192,168,1,1);
    // IPAddress gateway(192,168,1,1);
    // IPAddress subnet(255,255,255,0);

    AsyncWebServer server(80);
void setup()
{

    Serial.begin(9600);
    WiFi.softAP(ssid,password);
    // WiFi.softAPConfig(local_ip,gateway,subnet);

    // Serial.print("Local IP : ");
    // Serial.println(WiFi.localIP());  // not working

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    pinMode(2,OUTPUT);
    digitalWrite(2,LOW);
    pinMode(4,OUTPUT);
    digitalWrite(4,HIGH);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
        {
            char buffer[500];
            sprintf(buffer, "{Dear User : inam, \r\n Toogle LED : 192.168.1.1/uri?led=1&state=1}");
            request->send(200, "application/json", buffer);
          
        });
    server.on("/hitme", HTTP_GET, [](AsyncWebServerRequest *request)
        {
            String name;
            char buffer[500];
            if(request->hasParam("name"))
            {
                name = request->getParam("name")->value();
                sprintf(buffer, "{name : %s}", name);
                request->send(200, "application/json", buffer);
            }
        });

    server.on("/switch" , HTTP_GET, [](AsyncWebServerRequest *request)
        {
            String led , state;
            char buffer[500];
            if(request->hasParam("led")&&request->hasParam("state"))
            {
                led = request->getParam("led")->value();
                state = request->getParam("state")->value();
                digitalWrite(led.toInt(),state.toInt());
                sprintf(buffer, "Updated state of led %s to %s", led,state);
                request->send(200,"text", buffer);
            }
            else
            {
                request->send(200, "text" , "Enter valid params..");
            }
        }
    );

        server.begin();

}

void loop()
{
  
}