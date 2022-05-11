/*
 * 1.Throttle Collector 
 *   pin A0
 * 2.Brake generator
 *   pin 13
 * 3.Speed Collector
 *   pin A1
 * 4.Speed Generator
 *   pin 11 
 * 5.Throttle Generator
 *   pin 10  
 * 6.Brake Output
 *   pin 8  
 */
//Set Pins
 #define thColPin A3
 #define thGenPin 10
 #define brakeColPin 8
 #define brakeGenPin 13
 #define speedColPin A0
 #define speedGenPin 11

 

/////////Variables 
//brake
byte brakeState; 

//throttle
double thSig;

//Speed
double speedColSig; 



////////Functions
double sigToVlt(double sig);
double readToWrite(double readVal);

//void Brake();
//void Throttle();
//void Speed();








 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(brakeColPin, INPUT);
  pinMode(speedGenPin, OUTPUT);
  pinMode(thGenPin, OUTPUT);
  pinMode(brakeGenPin, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
 Throttle();
 Brake();
 Speed();

}





double sigToVlt(double sig){return sig * 5 / 1024;} //convert the input signal to voltage (1024 -> 5 range)
double readToWrite(double readVal){return readVal * 255 / 1024;}//convert the input signal to output signal (1024 -> 255 range)

void Brake(){digitalWrite(brakeGenPin,digitalRead(brakeColPin));}//Read the value from the switch and write the digital value
void Throttle(){analogWrite(thGenPin,readToWrite(analogRead(thColPin)));}//Read the value from potentiometer and Write the analog output value
void Speed(){
float frequency = map(analogRead(speedColPin),0,1024,1,230);
float period = 1000/frequency;
//Serial.println(period);
analogWrite(speedGenPin,readToWrite(analogRead(speedColPin)));
digitalWrite(speedGenPin,HIGH);
delay(period/2);
digitalWrite(speedGenPin,LOW);
delay(period/2);
  
}
