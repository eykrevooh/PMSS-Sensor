#ifndef sensor_h
#define sensor_h

#include <DHT.h>
class Sensor
{
  private:
    float temp_, hum_;                        //Variables: temp_ holds most recent temp reading, hum_ most recent humidity reading
    DHT dht_ = DHT(1,11);                     //Instantiation: dht_ is a dht 11 at pin 1
    float find_average_(int num_readings);    //Function: Updates temp_ and hum_ as averages of readings up to num_readings
  public:     
    Sensor(int pin, int dht_type);            //Constructor: define senser by pin number and dht type (11 or 22)
    float get_temp();                         //Function: returns temp_
    float get_hum();                          //Function: returns hum_
    int read();                               //Function: read from sensor and sets temp_ and hum_
  };
#endif

