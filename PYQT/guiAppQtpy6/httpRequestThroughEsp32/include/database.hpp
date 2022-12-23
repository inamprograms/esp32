#ifndef DATABASE_HPP
#define DATABASE_HPP

// #define WIFI_SSID "eduroam"
// #define WIFI_PASSWORD "INAM#6122"
#define WIFI_SSID "EPTeckS"
#define WIFI_PASSWORD "epteck@123S"

#define HOST "172.168.168.79"
#define HTTP_PORT 5000



#define PATCH_LED_BTN_STATUS 0


#define CNIC "12345"
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