#include "SoftwareSerial.h"

class Wifi {

private:
    String SSID;
    String password;
    String server;
    int wifi_rxpin; // Default  = 8;
    int wifi_txpin; // Default = 9;
    int wifi_baudrate; // Default = 2400;
    bool wifi_connected = false;
    SoftwareSerial *esp;

public:

    Wifi(); //Constructor method
    
    void set_baudrate(int baudrate);
    /* ----------- SETTER FUNCTIONS ------- */
    
    void set_rx_tx(int rx, int tx);
    
    void set_server(String servername);
    
    void set_credentials(String ssid, String password);

    void setup();
    /* ------------------------------------*/
    
    void reset();
    
    bool connect();

    void send_data (data d);
    
};

