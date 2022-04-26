#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H


#include "Arduino.h"

double sigToVlt(double sig);
int vltToSig(double volt);
int readToWrite(double sig);




class MotorController {
  private:
    uint8_t speedReadPin;
    uint8_t motorWritePin;
  public:
    MotorController(); 
    void setPinIn(uint8_t pin);
    void setPinOut(uint8_t pin,uint8_t channel);
    void motorWrite(double vlt);
    float motorSimulatorRead();
};




class ThrottleController {
  private:
    uint8_t thIn;
  public:
    ThrottleController();
    void setPinIn(uint8_t pin);
    float throttleRead();
};




class BrakeController {
  private:
    uint8_t brakeIn;
    long vlt;
    
  public:
    BrakeController();
    void setPinIn(uint8_t pin);
    byte brakeRead();
};





class BatteryController{
  private:
    uint8_t batteryPin;

  public:
  BatteryController(); 
  void setPinIn(uint8_t pin);
  int readInPercent(); 
  
  
};

class CurrentController{
  private:
    uint8_t currentPin;

  public:
  CurrentController(); 
  void setPinIn(uint8_t pin);
  int currentRead(); 
  
  
};

#endif
