#ifndef DATABASE_HPP
#define DATABASE_HPP

// #define WIFI_SSID "eduroam"
// #define WIFI_PASSWORD "INAM#6122"
#define WIFI_SSID "Inam ul Rehman"
#define WIFI_PASSWORD "in123456"

#define HOST "192.168.43.248"
#define HTTP_PORT 5000

#define POST_DATA 0
#define PUT_DATA 1
#define LED_STATUS_PATCH 3
#define DELETE_DATA 4

#define CNIC "3540173791213"
#define SEND_DATA_URI "/send_data"
#define GET_DATA_URI "/retrieve_data/"
#define CONTENT_TYPE "application/json"

#include <stdint.h>
class database
{
private:
    
public:
    database();
    ~database();
    void connectToWifi();
    void connectToDatabase();
    void send_data(uint8_t data);
    void retrieve_data();
};







#endif