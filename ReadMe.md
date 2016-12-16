API Documentation
=================

Table of Contents
=================
* [Dependencies]( #build)
* [Wi-Fi](#wi-fi)
* [Power](#power)
* [Sensor](#sensor)

Dependencies
=====
The following are dependencies needed by the project:
[Low Power](https://github.com/rocketscream/Low-Power)
[Unified Sensor Library](https://github.com/adafruit/Adafruit_Sensor)
[DHT Sensor Libary](https://github.com/adafruit/dht-sensor-library)


Wi-Fi
===

**Wifi(int rx, int tx, int baudrate, String servername, String ssid, String password)**

 This creates a wi-fi object that will allow us to connect to the esp8266.

**set\_baudrate(int baudrate)**

Built-in method used to set default rate at which data will be sent. The parameter &#39;baudrate&#39; is an integer datatype that specifies the baud rate of the software serial object.

**set\_rx\_tx(int rx, int tx)**

Built-in method used to designate default pins for sending and receiving data. The parameters &#39;rx&#39; and &#39;tx&#39; are pin values for the receiver and transmitter pins, respectively.

**set\_server(String servername)**



Built-in method used to specify the default server name to which data will be sent for reading. The parameter &#39;servername&#39; is the name of the server.



**set\_credentials(String ssid, String password**)

Built-in method used to designate the name and password for the default wi-fi connection. The parameters &#39;ssid&#39; and &#39;password&#39; are the network name and network password, respectively.

**setup()**

Method defined to set up the esp8266 wifi module. The software serial object is defined and initiated.



**reset()**

Method defined to reset the esp8266.



**connect()**

Method defined to connect the wi-fi module to network specified by the instance variables, SSID and password.



**send\_data()**

Method defined to send GET requests to the web server using the TCP connection that it establishes.

```cpp

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
```
Power
===

**Power(int pin)**

This creates a power object that will allow us to put the arduino into the suitable power consumption state (Power down). The parameter ‘pin’ sets which analog pin must be used for the voltage divider.


**sleep(float hours)**

Built-in method used to put the arduino in the low power sleep mode to conserve battery. The parameter ‘hours’ is the duration the system must be in the low power state.


**readVoltage()**

This built-in method reports the battery level left. Returns an integer value between 0 to 1023. 0 means battery is dead and 1023 battery is full.

**Example Usage**
```cpp
#include "Power.h"

#define VOLTAGE_PIN 0

Power power(VOLTAGE_PIN);

void setup(){
  Serial.begin(9600);
}

void loop(){
      power.readVoltage();
      power.sleep(0.005); // pass in the number of hours to sleep
    }
}
```


Sensor
===

**read()**
Does only one read on the sensor and sets the hum_ and temp_ sensors to the values that it reads. In the event of an error a 1 is returned otherwise a 0 is returned.

**find_average()**
Does 5 readings using the read function and returns the average obtained by those readings.

**get_temp()**
Returns the temperature obtained from the sensor. This method requires that the read() method be called prior to the get_temp method

**get_hum()**
Similar to the get temperature method in that it will return the humidity of the sensor after calling the read().
