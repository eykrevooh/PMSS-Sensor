//All library and class inclusions
#include <stdlib.h>
#include <stdio.h>

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
  //WIFI Globals
#define TX 8
#define RX 9
#define SSID "WifiGroup"
#define PWRD ""
#define SERVERNAME "192.168.0.100"

  //Other
#define BAUDRATE 2400
#define NUM_READ 5              //
#define NUM_SLEEP 8             //
#define RATE 2                  //
#define LED_PIN 4               // what digital pin is LED
#define BATTERY_PIN 0           //

//Initialize All Global Variables
int STATE = READ;
int SLEEP_COUNTER = 0;
bool CONNECTED;
bool SENT;


//Initialize Data Object

//Initialize WIFI Object

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
  //pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUDRATE);
    Serial.println("I am Running");

  //dht.begin();
}

void loop(){
  //Declare Dynamic Variables
  float TEMP_READINGS[NUM_READ];
  float HUM_READINGS[NUM_READ];
  bool SENT;
    
}
