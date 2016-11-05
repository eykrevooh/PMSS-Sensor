#ifndef sensor_h
#define sensor_h

#include <DHT.h>
class Sensor
{
  private:
    float temp_, hum_;
    DHT dht_ = DHT(1,11);
    float find_average_();
  public:
    Sensor(int pin, int dht_type);
    float get_temp();
    float get_hum();
    float read();
  };
#endif
