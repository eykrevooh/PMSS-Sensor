#include "Wifi.h"
#include "Arduino.h"
   
   Wifi::Wifi(int rx, int tx, int baudrate)
{
    set_rx_tx(rx, tx);
    set_baudrate(baudrate);
    setup();
}
  
    /* ----------- SETTER FUNCTIONS ------- */

    void Wifi::setup() {
      esp = new SoftwareSerial(wifi_rxpin, wifi_txpin);
      esp->begin(wifi_baudrate);
      reset();
      
    }
    
    void Wifi::set_baudrate(int baudrate) {
        wifi_baudrate = baudrate;
    }
    
    void Wifi::set_rx_tx(int rx, int tx) {
        wifi_rxpin = rx;
        wifi_txpin = tx;
    }
    
    void Wifi::set_server(String servername) {
        server = servername;
    }
    
    void Wifi::set_credentials(String ssid, String password) {
        SSID = ssid;
        password = password;
    }

    /* ------------------------------------*/
    
    
    
    void Wifi::reset() {
    /*Resets the Wifi chip*/
    esp->println("AT+RST"); 
    delay(1000); //Optional
    if(esp->find("OK") ) {
      Serial.println("Module Reset");
    } 
    }
    
    bool Wifi::connect() {
    /*Connects the Wifi to the appropriate network
    */

    String cmd = "AT+CWJAP=\"" +SSID+"\",\"" + password + "\"";
    esp->println(cmd);
    delay(4000); //Optional

    if (esp->find("OK")) {         // Print if the ESP8266 Wi-Fi chip has found the network, 
        Serial.println("Connected!");
        return true;
    }

    else {
        Serial.println("Cannot connect to wifi");
    }
    return false;
    }

    void Wifi::send_data (data d) {
  
     /* Sends data to the web server using the struct parameter 'data'
    Params: data is a struct which includes <key>, <tag>, <value> members
          server is the string value that includes the server name. For Example: 192.168.0.101
    */
  
        Serial.println("Connecting to server");
    
        //Incoming needs to be a struct with all of the data that goes to the uri specified
    
        //String uri = "/" + data.key + "/" + data.tag + "/" + data.value + "/";
      String sensor_id = String(d.sensor_id);
      String dht11_temp = String(d.dht11_temp);
      String dht11_hum = String(d.dht11_hum);
      String dht22_temp=String(d.dht22_temp);
      String dht22_hum = String(d.dht22_hum);
      String voltage = String(d.voltage);
      String uri = "/ABCD/"+sensor_id+ '/' +"TMP11"+'/'+dht11_temp;
      /* Needs modification */
      esp->println("AT+CIPSTART=\"TCP\",\"" + server + "\",5000"); //Start a TCP Connection with 'server'
    
      if  ( esp->find("OK")) {
        Serial.println("TCP connection ready");
      } 
      
      delay(1000);
    
       String postRequest =
          
      "GET " + uri + " HTTP/1.1\r\n" +
      "Host: " + server + "\r\n" + 
      "Connection: close\r\n" +
      "\r\n";
    
      String sendCmd = "AT+CIPSEND=";
    
      esp->print(sendCmd);
      esp->println(postRequest.length() );
      delay(500);
    
      if(esp->find(">")) { Serial.println("Sending.."); esp->print(postRequest);
    
      if( esp->find("SEND OK")) { Serial.println("Packet sent");
    
      // while (esp->available()) {
    
      // String tmpResp = esp->readString();
      // Serial.println(tmpResp);
    
      // }
    
      // close the connection
      esp->println("AT+CIPCLOSE");
    
    }}

    }


