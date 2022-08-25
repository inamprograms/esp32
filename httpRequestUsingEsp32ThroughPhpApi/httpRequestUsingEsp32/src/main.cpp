#include <Arduino.h>
#include"database.hpp"

database obj;
void setup() {
    Serial.begin(9600);
    Serial.println("starting esp32");

    obj.connectToWifi();
    obj.connectToDatabase();
    obj.send_data();
  
}

void loop() {
  
}