#include <Arduino.h>
#include"database.hpp"

database obj;
void setup() {
    Serial.begin(9600);
    Serial.println("starting esp32");

    obj.connectToWifi();
    obj.connectToDatabase();
    // obj.send_data(POST_DATA);
    // obj.send_data(PUT_DATA);
    // obj.send_data(LED_STATUS_PATCH);
    // obj.send_data(DELETE_DATA);
    obj.receive_data();
  
}

void loop() {
  
}