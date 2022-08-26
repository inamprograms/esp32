#include<WiFi.h>
// HI new
const char *ssid = "Inam ul Rehman";
const char *password = "in123456";

void setup(){
  Serial.begin(9600);
  
  WiFi.begin(ssid,password);
  Serial.println("Connecting to wifi..");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("<");
    delay(1000);
    Serial.println("<connecting>");
  }

  Serial.println("Connected to Wifi");
  Serial.print("SSID: ");
  Serial.print(WiFi.SSID());
  Serial.print(", RSSI: ");
  Serial.println(WiFi.RSSI());
  // Serial.print("Local Esp32 IP address: ");
  // Serial.println(WiFi.localIP());


}

void loop(){


}