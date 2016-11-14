#ifndef data_h
#define data_h

typedef struct Data{
  String sensor_id;
  float dht11_temp;
  float dht11_hum;
  float dht22_temp;
  float dht22_hum;
  float voltage;
} data;

#endif
