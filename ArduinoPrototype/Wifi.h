#include "SoftwareSerial.h"

typedef struct Data{

  char sensor_id;
  float dht11_temp;
  float dht11_hum;
  float dht22_temp;
  float dht22_hum;
  float voltage;
  }data;
  
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

