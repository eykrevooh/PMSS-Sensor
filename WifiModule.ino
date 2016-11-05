#include "Wifi.h"

 data package; //Struct instance of data
 
 Wifi wifi; // Initializing a wifi object
 
void setup() {
   Serial.begin(9600);
   
   /* The following will have to change eventually */ 
   
   package.sensor_id ='a';
   package.dht11_temp = 70.99;
   package.dht11_hum = 55.44;
   package.dht22_temp = 73.33;
   package.dht22_hum = 53.076;
   package.voltage = 3.23;


   /* Setting wifi instance variables */
   wifi.set_baudrate(2400);
   wifi.set_rx_tx(8, 9);
   wifi.set_server("192.168.0.101");
   wifi.set_credentials("WifiGroup", "");
   wifi.setup();
   wifi.connect();

}

void loop() {
  wifi.send_data(package);
  delay(10000);
}
