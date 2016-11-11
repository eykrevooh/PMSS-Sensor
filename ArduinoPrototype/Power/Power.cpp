#include "Power.h"
#include "Arduino.h"

Power::Power(int pin){
  voltagePin = pin;
}

int Power::sleep(float hours){
  int seconds = (int) 3600*hours;
  int i;
  for ( i=0; i<seconds; i++){
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  }

}

void Power::readVoltage(){
  analogReference(INTERNAL);
  int val;
  val = analogRead(BATTERY_PIN);
  Serial.print("Battery voltage is: ");
  Serial.println(val);
  return val;
}
