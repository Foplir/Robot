#include <DynamixelWorkbench.h>

#if defined(OPENCM904)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(OPENCR)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE   1000000
#define first    1
#define second    2

int speed = 500;

//pins front
int trigPinR = 12; 
int echoPinR = 13; 
int trigPinL = 14; 
int echoPinL = 15; 

//pins back
int trigPinRB = 16;
int echoPinRB = 17;
int trigPinLB = 18;
int trigPinLB = 19;


byte bufferCheck;
int LightSensorPin = 1;

DynamixelWorkbench motor;
  uint8_t first = DXL_ID1;
  uint8_t second = DXL_ID2;


void setup() 
{
  Serial.begin(57600);
  pinMode(trigPinL, OUTPUT); 
  pinMode(echoPinL, INPUT); 
  pinMode(trigPinR, OUTPUT); 
  pinMode(echoPinR, INPUT); 
  digitalWrite(trigPinR, LOW);
  digitalWrite(trigPinL, LOW); 
  pinMode(LightSensorPin, INPUT);

  while (!motor.init(DEVICE_NAME, BAUDRATE));
  motor.ping(first);
  motor.ping(second);
  motor.wheelMode(first, 0);
  motor.wheelMode(second, 0);     
  delay(5000);
}

void loop() 
{
  switch(FB(dist(trigRF, echoRF), dist(trigLF, echoLF), dist(trigRB, echoRB), dist(trigLB, echoLB)))
  {
    case true:
      //спереди
      if RL(dist(trigRF, echoRF), dist(trigLF, echoLF)) 
      break;

    case false:
      //взади
      break;

  }

}

/*
(true) - переднее значение меньше
(false) - заднее значение меньше
*/
bool FB(int RF, int LF, int RB, int LB)
{
  if (min(RF, LF) < min(RB, LB)){
      return true;
  } else return false;
}

/*
(true) - правое значение меньше
(false) - левое значение меньше
*/
bool RL(int R, int L)
{
  if (R<L){
    return true;
  } else return false;
}

void motorL(){
  motor.goalVelocity(first, (int32_t)-speed);
  motor.goalVelocity(second, (int32_t)speed);
}
void motorR(){
  motor.goalVelocity(first, (int32_t)speed);
  motor.goalVelocity(second, (int32_t)-speed);  
}
void motorF(){
  motor.goalVelocity(first, (int32_t)speed);
  motor.goalVelocity(second, (int32_t)speed);
}
void motorB(){
  motor.goalVelocity(first, (int32_t)-speed);
  motor.goalVelocity(second, (int32_t)-speed);  
}

int dist(int trigPin, int echoPin)
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH)/58;
}

