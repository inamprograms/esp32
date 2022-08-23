#include<WiFi.h>
#include<ESPAsyncWebServer.h>

const char *ssid = "Inam ul Rehman";
const char *password = "in123456";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid,password);
  Serial.println("Connecting to Network...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("<");
    delay(100);
    Serial.println("<connecting>");
  }
  Serial.println("Connected to wifi.");
  Serial.print("Local Ip: ");
  Serial.println(WiFi.localIP());

  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);


  server.begin();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    
    request->send_P(200, "text", "Welcome to our HOME page");
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
      });
}

void loop() {
  
}