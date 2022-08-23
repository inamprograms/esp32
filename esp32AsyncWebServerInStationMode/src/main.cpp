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

  server.begin();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    
    request->send_P(200, "text", "Welcome to our HOME page");
  });
}

void loop() {
  
}