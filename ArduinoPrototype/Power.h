/**
    CS-386 Embedded Systems
    Power.h
    Purpose: Header file for the power class

    @author Ishwar Agarwal, Annie He, William Mosier, Xhafer Rama, Dadbeh Shaddel
    @version 0.1 11/28/16
*/

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
};

#endif
