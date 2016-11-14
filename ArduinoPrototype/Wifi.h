#ifndef wifi_h
#define wifi_h

#include "SoftwareSerial.h"
#include "Data.h"

class Wifi {

private:
    String SSID;
    String password;
    String server;
    int wifi_rxpin; 
    int wifi_txpin; 
    int wifi_baudrate;
    bool wifi_connected = false;
    SoftwareSerial *esp;

public:

    Wifi(int rx, int tx, int baudrate, String servername, String ssid, String password); //Constructor method
    
    void set_baudrate(int baudrate);
    /* ----------- SETTER FUNCTIONS ------- */
    
    void set_rx_tx(int rx, int tx);
    
    void set_server(String servername);
    
    void set_credentials(String ssid, String password);

    void setup();
    /* ------------------------------------*/
    
    void reset();
    
    bool connect();

    bool send_data (data d);
    
};

#endif
