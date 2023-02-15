/* Импорт библиотек*/
#include "math.h"

/* Устанавливаем значение переменных */

/* Значения пинов */
byte motorA;
byte motorB;
byte sensorFA;
byte sensorFB;
byte sensorBA;
byte sensorBB;
byte sensorColor;

/* Остальные значения */
int durationFA;
int durationFB;
int durationBA;
int durationBB;
float distFA;
float distFB;
float distBA;
float distBB;


//функция для преобразования значения датчикав см
float toCm(float duration){
  return (duration/2)/29;
};

//функция действия после выбора стороны робота
void action(float distA, float distB){
  //противник найден
  while(distA>0 && distB>0){
    //ехать вперед

  };

  //противник ушел влево
  while(distA>0 && distB<=0){
    //поворачивать влево

  };

  //противник ушел вправо
  while(distA<=0 && distB>0){
    //поворачивать вправо

  };
};


void setup() {
  //настройка пинов
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(sensorFA, INPUT);
  pinMode(sensorFB, INPUT); 
  pinMode(sensorBA, INPUT);
  pinMode(sensorBB, INPUT);
  pinMode(sensorColor, INPUT);

  //настройка вывода в консоль
  Serial.begin(9600);
}



void loop() {
  
  //считывание волны
  durationFA = pulseIn(sensorFA, HIGH);
  durationFB = pulseIn(sensorFB, HIGH);
  durationBA = pulseIn(sensorBA, HIGH);
  durationBB = pulseIn(sensorBB, HIGH);
  
  //преобразование значения датчиков в см 
  distFA = toCm(durationFA);
  distFB = toCm(durationFB);
  distBA = toCm(durationBA);
  distBB = toCm(durationBB);
  
  //задержка для корректной работы датчиков
  delay(100);
}

void yield(){
    if (fmin(distFA, distFB) < fmin(distBA, distBB)){
      action(distFA, distFB);
    } else {
      action(distBA, distBB);
    };

}
