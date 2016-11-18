#include <DHT.h>
#include "sensor.h"
#include "Arduino.h"

Sensor::Sensor(int pin, int dht_type){
  dht_ = DHT(pin, dht_type);
}

int Sensor::read(){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    hum_ = dht_.readHumidity();
    // Read temperature as Celsius (the default)
    temp_ = dht_.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(hum_) || isnan(temp_)) {
      Serial.println("Failed to read from DHT sensor!");
      return 1;
    }
  return 0;
}

float Sensor::find_average_(int num_readings){
  //Average the sensors reading
  float total_temp;
  float total_hum;
  for (int i=0; i<num_readings; i++){
          Sensor::read();
          total_temp += Sensor::get_temp();
          total_hum += Sensor::get_hum();
        }
  temp_ = av_temp / num_readings;
  hum_ = av_hum / num_readings;
  return 0;
  }

float Sensor::get_temp(){
  Serial.print("Temperature: ");
  Serial.println(temp_);
  return temp_;
}

float Sensor::get_hum(){
  Serial.print("Humidity: ");
  Serial.println(hum_);
  return hum_;
}
