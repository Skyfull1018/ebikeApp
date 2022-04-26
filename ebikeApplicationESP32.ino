/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include <EspMQTTClient.h>
#include "DeviceController.h"

/////MQTT Configuration//////////////////////////////////////
String subTopic = "publish/Oculus";
String pubTopic = "subscribe/Oculus";
int recvState = 9;


 EspMQTTClient client(
    "yes1",
    "UOMEEE123",
    "192.168.68.104",
    "FirstEspConnection",
    1883
    );
    
  void onConnectionEstablished()
  {
    client.subscribe(subTopic, [](const String & payload){recvState = payload.toInt();Serial.println(payload);});
    client.publish(pubTopic, "This is a message");
  }
/////////////////////////////////////////////////////
   

///////Wheel Velocity Measureing Variables and Functions////////////////
unsigned long currentTime;
unsigned long previousTime;
unsigned long pulsePeriod;
float frequency;
float velocity;
unsigned int maxInterval = 350;
unsigned long checkTime;
unsigned long prevCheck;
unsigned long interval;
byte checkState;
//Functions//
void checkZeroVelocity();
void speedMeasurement();
///////////////////////////////////////////////////////////////////////////

///////////////Device Controller declaration/////////////////////
MotorController motor;
ThrottleController  throttle;
BatteryController battery;
BrakeController brakeRight;
BrakeController brakeLeft; 
CurrentController current;
//////////////////////////////////////////////////////////////////



void setup(){
  Serial.begin(115200);
  client.enableDebuggingMessages();

  
  throttle.setPinIn(35);
  battery.setPinIn(35);
  brakeRight.setPinIn(32);
  brakeLeft.setPinIn(33);
  motor.setPinIn(35);
}





void loop(){
client.loop();
int count = 10;
switch(recvState){
  
  case 0:  //Battery State
  {
     client.publish(pubTopic,String(battery.readInPercent()));
     break;
  }
  case 1:  //Brake
  {
    String msg = String(brakeLeft.brakeRead())+"&"+String(brakeRight.brakeRead());
    client.publish(pubTopic,msg);
    break;
  }
  case 2: //Throttle
  {
    client.publish(pubTopic,String(throttle.throttleRead()));
    delay(100);
    break;
  }
  case 3: //Speed
  {
    
    client.publish(pubTopic,String(5));
    delay(100);
    break;
  }
    case 32: //Speed
  {
    
    client.publish(pubTopic,String(10));
    delay(100);
    break;
  }
   case 33: //Speed
  {
   
    client.publish(pubTopic,String(20));
    
    delay(100);
    break;
  }
  case 34: //Speed
  {
    
    client.publish(pubTopic,String(30));
    delay(100);
    break;
  }

   case 35: //Speed
  {
    
    client.publish(pubTopic,String(40));
    delay(100);
    break;
  }
  
  case 4://Current
  {
    float sig = analogRead(35);
    float sigPer = sig / 4093 * 300;
    client.publish(pubTopic,String(sigPer));
    delay(100);
    break;
  }
  
  default: Serial.println("Nothing"); break;
}
delay(10);
}





void checkZeroVelocity(){
  checkState = digitalRead(2);
  if(checkState == HIGH){
    checkTime = millis();
  }
  if(millis() - checkTime > maxInterval){
    velocity = 0;
  }

}
void speedMeasurement(){
  currentTime = micros(); 
  pulsePeriod = currentTime - previousTime;
  frequency  = 1000000/pulsePeriod;
  velocity = 0.169491*frequency;
  previousTime = currentTime; 
}
