
#include <stdlib.h>
#include <stdio.h>
#include <LowPower.h>
#include <DHT.h>

//Declaring All States
#define INIT 0
#define CONNECT_WIFI 1
#define WRITING_LOCAL 2
#define WRITING_WEB 3
#define DISCONNECT_WIFI 4
#define SLEEP 5
#define READ 6

//Delcare all Constant variables
#define NUM_READ 5
#define NUM_SLEEP 8
#define RATE 2
#define LED_PIN 4    // what digital pin is LED
#define DHTPIN 2     // what digital pin is DHT
#define DHTTYPE DHT11   // DHT 11
#define BATTERY_PIN 0

DHT dht(DHTPIN, DHTTYPE);

// Keep track of the states, start with INIT
int state = INIT;
int SLEEP_COUNTER = 0;

void blinkLED() {
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

void readDHT() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
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
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  //Declare Dynamic Variables
  float TEMP_READINGS[NUM_READ];
  float HUM_READINGS[NUM_READ];
  int CONNECTED;

  switch(state){

    case INIT:
      //////////
      //This is the first state
      //////////
      blinkLED();
      state = READ;

    case READ:
      //////////
      //READ FROM SENSOR AND WRITE TO TEMP_READING AND HUM_READINGS ARRAY
      //////////

      //////////
      //FIND AVERAGE READING VALUE
      //////////
      Serial.println("READ FROM SENSOR");
      readDHT();
      readVoltage();
      state = CONNECT_WIFI;
      break;
    
    case CONNECT_WIFI:
      //////////
      //CONNECT TO THE WIFI
      //////////
      CONNECTED = 0; //This is for testing
      blinkLED();
      if(CONNECTED){
        state = WRITING_WEB;
      }
      else{
        state = WRITING_LOCAL;
      }
      Serial.println("CONNECTING TO WIFI");
      break;

    case WRITING_LOCAL:
      ////////////
      //WRITE THE VALUE LOCALLY
      ////////////
      Serial.println("WRITING LOCALLY");
      blinkLED();
      state = SLEEP;
      break;

     case WRITING_WEB:
      /////////////
      //WRITE THE VALUE TO THE WEB
      /////////////
      Serial.println("WRITING TO WEB");
      blinkLED();
      state = DISCONNECT_WIFI;
      break;

     case DISCONNECT_WIFI:
      /////////////
      //DISCONNECT FROM THE WIFI
      /////////////
      Serial.println("DISCONNECTING FROM WIFI");
      blinkLED();
      state = SLEEP;
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
          state = READ;      
          SLEEP_COUNTER = 0;
        }
      break;
    }
}
