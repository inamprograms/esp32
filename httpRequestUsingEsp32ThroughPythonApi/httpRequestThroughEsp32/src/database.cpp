#include<Arduino.h>
#include<WiFi.h>
#include"database.hpp"

WiFiClient client;
database::database()
{
    Serial.println("constructor");
}

database::~database()
{
    Serial.println("destructor");
}

void database::connectToWifi()
{
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("<");
        delay(1000);
        Serial.println("Connecting");
    }

    Serial.println("Connected to WiFi Network.");

    Serial.print("Esp32 Local IP");
    Serial.println(WiFi.localIP());
}

void database::connectToDatabase()
{
    if (!client.connect(HOST,HTTP_PORT))
    {
        Serial.println("Connection failed");
        return;
    }
    Serial.println("Connected With database.");
    
}

void database::send_data(uint8_t data)
{
    char packet[1000];
    char payload[500];
    int contentLength;

   
    switch (data)
    {
    case POST_DATA:
        contentLength = sprintf(payload, "{ \"cnic\" : \"%s\", \"temperature\" : \"%i\", \"humidity\" : \"%i\", \"led_status\" : \"%i\", \"btn_status\" : \"%i\"}",CNIC,500,600,1,1);
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
        contentLength = sprintf(payload, "{\"cnic\" : \"%s\", \"temperature\" : \"%i\", \"humidity\" : \"%i\", \"led_status\" : \"%i\", \"btn_status\" : \"%i\"}",CNIC,100,100,0,0);
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
        contentLength = sprintf(payload, "{\"cnic\" : \"%s\", \"led_status\" : \"%i\"}",CNIC,1);
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
        contentLength = sprintf(payload, "{\"cnic\" : \"%s\"}",CNIC);
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

void database::retrieve_data()
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