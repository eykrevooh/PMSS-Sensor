/**
    CS-386 Embedded Systems
    Power.cpp
    Purpose: Contains the power class that sleeps and reads voltage

    @author Ishwar Agarwal, Annie He, William Mosier, Xhafer Rama, Dadbeh Shaddel
    @version 0.1 11/28/16
*/

#include "Power.h"
#include "Arduino.h"

Power::Power(int pin){
  voltagePin = pin; // set the analog pin to read voltage
}

/*
Sleep method sleeps for given number of hours as floating point
The processor is in a powered down state after the function is executed
*/
void Power::sleep(float hours){
  int seconds, i;
  seconds = (int) 3600*hours;

  for ( i=0; i<seconds; i++){
    // use the RocketScream LowPower libraries powerDown nmethod
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  }

}

/*
This method reads voltage in the battery using the internal reference
The returned number is an int between 0-1023; 1023 being battery is filled
*/
int Power::readVoltage(){
  int val;

  analogReference(INTERNAL);
  val = analogRead(voltagePin);
  //Serial.print("Battery voltage is: ");
  //Serial.println(val);
  return val;
}
