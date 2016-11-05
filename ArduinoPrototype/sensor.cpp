#include <DHT.h>
#include "sensor.h"
#include "Arduino.h"

Sensor::Sensor(int pin, int dht_type){
  dht_ = DHT(pin, dht_type);
}

float Sensor::read(){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht_.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht_.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht_.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return 0.0;
    }
    return 0.0;
}
// Compute heat index in Fahrenheit (the default)
/* float hif = dht.computeHeatIndex(f, h); */
/* // Compute heat index in Celsius (isFahreheit = false) */
/* float hic = dht.computeHeatIndex(t, h, false); */

/* Serial.print("Humidity: "); */
/* Serial.print(h); */
/* Serial.print(" %\t"); */
/* Serial.print("Temperature: "); */
/* Serial.print(t); */
/* Serial.print(" *C "); */
/* Serial.print(f); */
/* Serial.print(" *F\t"); */
/* Serial.print("Heat index: "); */
/* Serial.print(hic); */
/* Serial.print(" *C "); */
/* Serial.print(hif); */
/* Serial.println(" *F"); */

float Sensor::find_average_(){
  //Average the sensors reading
  return 0.0;
  }

float Sensor::get_temp(){
  return 0.0;
}

float Sensor::get_hum(){
  return 0.0;
}
