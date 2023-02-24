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
int distanceR, distanceL;
int duration;
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
  //delay(5000);
}

void loop() 
{
  switch(check(dist(trigRF, echoRF), dist(trigLF, echoLF), dist(trigRB, echoRB), dist(trigLB, echoLB)))
  {
    case 1:
      //правый спереди
      motor.goalVelocity(first, (int32_t)-speed);
      motor.goalVelocity(second, (int32_t)speed);
      break;

    case 2:
      //левый спереди
      break;

    case 3:
      //правый взади
      break;

    case 4:
      //левый взади
      break;
  }

}

/*
(1) - меньшее значение на правом спереди
(2) - меньшее значение на левом спереди

(3) - меньшее значение на правом взади
(4) - меньшее значение на левом взади

подавать значение в след. порядке: 1-П_спереди, 2-Л_спереди, 3-П_взади, 4-Л_взади
*/
int check(int RF, int LF, int RB, int LB)
{
  if (min(RF, LF) < min(RB, LB)){
    if (RF < LF){
      return 1
    } else {
      return 2
    }
  } else {
    if (RB < LB){
      return 3
    } else {
      return 4
    }
  }
    
}


int dist(int trigPin, int echoPin)
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH)/58;
}

