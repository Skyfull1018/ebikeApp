#include "deviceController.h"
#include <Arduino.h>
#include "math.h"

double sigToVlt(double sig){return sig * 3.3 / 4095.0;};
int vltToSig(double volt){return volt / 3.3 * 255;};
int readToWrite(double sig){return sig *255 / 4095.0;};




////////////////////////Motor////////////////////////////////////////
MotorController::MotorController(){};
void MotorController :: setPinIn(uint8_t pin){ speedReadPin = pin;}
void MotorController :: setPinOut(uint8_t pin, uint8_t channel){
  motorWritePin = pin; 
  ledcAttachPin(pin, channel);
};
void MotorController::motorWrite(double outVlt){ledcWrite(motorWritePin,vltToSig(outVlt));};
float MotorController::motorSimulatorRead(){
  float motorSig = analogRead(speedReadPin);
  float motorSigMap = motorSig * 40.0 / 4093;
  return motorSigMap;
}
////////////////////////////////////////////////////////


///////////////////////////Throttle///////////////////////////////
ThrottleController::ThrottleController(){};
void ThrottleController::setPinIn(uint8_t pin){thIn=pin;};
float ThrottleController::throttleRead(){ 
  float thSig = analogRead(thIn); 
  float thSigPer = thSig /4093 * 2.95;
  return thSigPer;
  };
//////////////////////////////////////////////////////////////////


/////////////////////////////Brake///////////////////////////////
BrakeController::BrakeController(){};
void BrakeController::setPinIn(uint8_t pin){
  brakeIn = pin;
  pinMode(brakeIn,INPUT);
  }; 
byte BrakeController::brakeRead(){return digitalRead(brakeIn);};

//////////////////////////////////////////////////////////////////////




//////////////////////BatteryController/////////////////////////
BatteryController::BatteryController(){};

void BatteryController::setPinIn(uint8_t pin){batteryPin = pin;}

int BatteryController::readInPercent(){
  int sig = analogRead(batteryPin)/100; 
  int sigPer = map(sig,0,40,0,100);
  return sigPer;
}
//////////////////////////////////////////////////////////////


//////////////////////BatteryController/////////////////////////
CurrentController::CurrentController(){};

void CurrentController::setPinIn(uint8_t pin){currentPin = pin;}

int CurrentController::currentRead(){
      unsigned int x=0;
      float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;
    for (int x = 0; x < 150; x++){ //Get 150 samples
      AcsValue = analogRead(A0);     //Read current sensor values   
      Samples = Samples + AcsValue;  //Add samples together
      delay (3); // let ADC settle before next sample 3ms
    }
      AvgAcs=Samples/150.0;//Taking Average of Samples
      AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) )/0.100;
      return AcsValueF;
}
//////////////////////////////////////////////////////////////////////
