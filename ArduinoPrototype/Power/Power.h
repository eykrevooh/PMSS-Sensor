#ifndef power_h
#define power_h

#include <LowPower.h>

class Power{
  private:
      int voltagePin;
  public:
      Power(int pin);
      void sleep(float hours);
      int readVoltage();
}
