#ifndef DATABASE_HPP
#define DATABASE_HPP

#define POST_DATA 0
#define PUT_DATA 1
#define DELETE_DATA 2
#define LED_STATUS_PATCH 3

#define CNIC "2345176513785467"
#define URI "/api/usersData.php"
#define HOST "192.168.43.248"
#define CONTENT_TYPE "application/json"


#define WIFI_SSID "Inam ul Rehman"
#define WIFI_PASSWORD "in123456"

#define HTTP_PORT 80



#include<stdint.h>
    class database
    {
    private:
        
    public:
        database();
        ~database();

        void connectToWifi();
        void connectToDatabase();
        void send_data();
        void receive_data();
    };

#endif