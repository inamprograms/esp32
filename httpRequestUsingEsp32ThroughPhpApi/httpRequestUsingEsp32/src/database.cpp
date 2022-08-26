#include<Arduino.h>
#include<WiFi.h>
#include"database.hpp"

WiFiClient client;
database::database()
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
    Serial.println("Connected with database"); 
    
    

}

void database::receive_data()
{
    int payloadIndex;
    char payload[500];
    char packet[1000];

    Serial.println("reading data using http get request");
    sprintf(packet, "GET %s?cnic=%s HTTP/1.1\r\nHOST:%s\r\n\r\n\r\n",URI,CNIC,HOST);
    Serial.println(packet);

    client.print(packet);
    String line;
    Serial.println("reading data");
    line = client.readString();
    Serial.print(line);
    Serial.println();

    for (int i = 0; i < line.length(); i++)
    {
        if(line[i] == '{')
        {
            payloadIndex = i;
            for (int j = payloadIndex; j < line.length(); j++)
            {
                payload[j-i]  = line[j];
                if (line[j] == '}')
                {
                    payload[j-i+1] = '\0';
                    break;
                } 
            }
        }
    }

    Serial.println("closing connection");
    Serial.println(payload);  
}