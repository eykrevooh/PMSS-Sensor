//All library and class inclusions
#include <stdlib.h>
#include <stdio.h>
#include <LowPower.h>
#include "sensor.h"
#include "Wifi.h"
#include <DHT.h>

//Declaring All STATEs
#define READ 0                  //Sensor Reads From Sensor In This State
#define CONNECT_WIFI 1          //Connects the Arduino to WIFI
#define WRITING_LOCAL 2         //If fails to connect to WIFI, write locally
#define WRITING_WEB 3           //If connects to WIFI, write values to web
#define DISCONNECT_WIFI 4       //Disconnects from WIFI
#define SLEEP 5                 //Arduino goes to deep sleep

//Delcare all Constant variables
  //Sensor ID Declaration
#define SENSOR_ID "Prot"
  //Sensor Pins
#define DHT11PIN 2
#define DHT22PIN 3
  //Other
#define NUM_READ 5              //
#define NUM_SLEEP 8             //
#define RATE 2                  //
#define LED_PIN 4               // what digital pin is LED
#define BATTERY_PIN 0           //

//Initialize All Global Variables
int STATE = READ;
int SLEEP_COUNTER = 0;

//Initialize All Global Class Objects
Sensor dht11(2, DHT11);

typedef struct Data{
  String sensor_id;
  float dht11_temp;
  float dht11_hum;
  float dht22_temp;
  float dht22_hum;
  float voltage;
} data;

//Initialize Data Object
data data_values;
  
void blinkLED() {
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

int readVoltage() {
  analogReference(INTERNAL);
  int val;
  val = analogRead(BATTERY_PIN);
  Serial.print("Battery voltage is: ");
  Serial.println(val);
  return val;
  }

void setup(){
  // Run one time setup.
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(2400);
  data_values.sensor_id = SENSOR_ID;
  //dht.begin();
}
void loop(){
  //Declare Dynamic Variables
  float TEMP_READINGS[NUM_READ];
  float HUM_READINGS[NUM_READ];
  int CONNECTED;

  switch(STATE){

    case READ:
      //////////
      //READ FROM SENSOR AND WRITE TO TEMP_READING AND HUM_READINGS ARRAY
      //////////
      dht11.read();
      data_values.dht11_temp = dht11.get_temp();
      data_values.dht11_hum = dht11.get_hum();
      //////////
      //FIND AVERAGE READING VALUE
      //////////
      Serial.println("READ FROM SENSOR");
      //readDHT();
      readVoltage();
      STATE = CONNECT_WIFI;
      break;

    case CONNECT_WIFI:
      //////////
      //CONNECT TO THE WIFI
      //////////
      CONNECTED = 0; //This is for testing
      connectToWifi();
      if(CONNECTED){
        STATE = WRITING_WEB;
      }
      else{
        STATE = WRITING_LOCAL;
      }
      Serial.println("CONNECTING TO WIFI");
      break;

    case WRITING_LOCAL:
      ////////////
      //WRITE THE VALUE LOCALLY
      ////////////
      Serial.println("WRITING LOCALLY");
      blinkLED();
      STATE = SLEEP;
      break;

     case WRITING_WEB:
      /////////////
      //WRITE THE VALUE TO THE WEB
      /////////////
      Serial.println("WRITING TO WEB");
      blinkLED();
      STATE = DISCONNECT_WIFI;
      break;

     case DISCONNECT_WIFI:
      /////////////
      //DISCONNECT FROM THE WIFI
      /////////////
      Serial.println("DISCONNECTING FROM WIFI");
      blinkLED();
      STATE = SLEEP;
      break;

     case SLEEP:
      //////////
      //SLEEP
      //////////
      Serial.println("SLEEPING");

      Serial.print("COUNTER is:");
      Serial.print(SLEEP_COUNTER);
      Serial.println(" ");

      if (SLEEP_COUNTER < ((NUM_SLEEP * RATE)/ 8)) {
        Serial.println("Going to sleep");
        delay(100);
        LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);
        SLEEP_COUNTER = SLEEP_COUNTER + 1;
      } else {
          STATE = READ;
          SLEEP_COUNTER = 0;
        }
      break;
    }
}
