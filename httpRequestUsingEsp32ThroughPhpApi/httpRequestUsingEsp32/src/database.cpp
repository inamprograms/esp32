#include<Arduino.h>
#include<WiFi.h>
#include"database.hpp"

WiFiClient client;
database::database(/* args */)
{
    Serial.println("Constructor called");
}
    
database::~database()
{
    Serial.println("Destructor called");
}

void database::send_data(uint8_t data)
{
    char payload[500];
    char packet[1000];
    int contentLength;

   
    switch (data)
    {
    case POST_DATA:
        contentLength = sprintf(payload, "{\"cnic\" : %s, \"temp\" : %i, \"hum\" : %i, \"ledStatus\" : %i, \"btnStatus\" : %i}",CNIC,500,600,1,1);
        sprintf(packet, "POST %s HTTP/1.1\r\nHOST:%s\r\nContent-type:%s\r\nContent-length:%i\r\n\r\n%s",URI,HOST,CONTENT_TYPE,contentLength,payload);
        Serial.println(packet);
        client.print(packet);
        while (client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }
        Serial.println();
        Serial.println("closing connection"); 
        break;
    case PUT_DATA:
        contentLength = sprintf(payload, "{\"cnic\" : %s, \"temp\" : %i, \"hum\" : %i, \"ledStatus\" : %i, \"btnStatus\" : %i}",CNIC,100,100,0,0);
        sprintf(packet, "PUT %s HTTP/1.1\r\nHOST:%s\r\nContent-type:%s\r\nContent-length:%i\r\n\r\n%s",URI,HOST,CONTENT_TYPE,contentLength,payload);
        Serial.println(packet);
        client.print(packet);
        while (client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }
        Serial.println();
        Serial.println("closing connection");
        break;
    case LED_STATUS_PATCH:
        contentLength = sprintf(payload, "{\"cnic\" : %s, \"ledStatus\" : %i}",CNIC,1);
        sprintf(packet, "PATCH %s HTTP/1.1\r\nHOST:%s\r\nContent-type:%s\r\nContent-length:%i\r\n\r\n%s",URI,HOST,CONTENT_TYPE,contentLength,payload);
        Serial.println(packet);
        client.print(packet);
        while (client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }
        Serial.println();
        Serial.println("closing connection");
        break;
    case DELETE_DATA:
        contentLength = sprintf(payload, "{\"cnic\" : %s}",CNIC);
        sprintf(packet, "DELETE %s HTTP/1.1\r\nHOST:%s\r\nContent-type:%s\r\nContent-length:%i\r\n\r\n%s",URI,HOST,CONTENT_TYPE,contentLength,payload);
        Serial.println(packet);
        client.print(packet);
        while (client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }
        Serial.println();
        Serial.println("closing connection");
        break;
   
    default:
        break;
    }

}

void database::connectToWifi()
{
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    Serial.println("Connecting to wifi network...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("<");
        delay(500);
        Serial.println("<connecting>");
    }
    Serial.println("Connected to WiFi");
    Serial.print("iP Allowed ");
    Serial.println(WiFi.localIP());
    
}

void database::connectToDatabase()
{
    if (!client.connect(HOST,HTTP_PORT))
    {
        Serial.println("connection failed");
    }
    else
    {
       Serial.println("Connected with database"); 
    }
    

}

