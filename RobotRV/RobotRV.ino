/* Устанавливаем значение переменных */

/* Значения пинов */
byte motorA;
byte motorB;
byte sensorFA;
byte sensorFB;
byte sensorRA;
byte sensorRB;
byte sensorLA;
byte sensorLB;
byte sensorBA;
byte sensorBB;
byte sensorColor;

/* Остальные значения */
float durationFA;
float durationFB;
float distFA;
float distFB;

void setup() {
  
  //настройка пинов
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(sensorFA, INPUT);
  pinMode(sensorFB, INPUT); 
  pinMode(sensorRA, INPUT);
  pinMode(sensorRB, INPUT);
  pinMode(sensorLA, INPUT);
  pinMode(sensorLB, INPUT);
  pinMode(sensorBA, INPUT);
  pinMode(sensorBB, INPUT);
  pinMode(sensorColor, INPUT);

  //настройка вывода в консоль
  Serial.begin(9600);
}

//функция для преобразования значения датчикав см
float toCm(float duration){
  return (duration/2)/29;
};

void loop() {
  
  //считывание волны
  durationFA = pulseIn(sensorFA, HIGH);
  durationFB = pulseIn(sensorFB, HIGH);
  
  //преобразование значения датчиков в см 
  distFA = toCm(durationFA);
  distFB = toCm(durationFA);

  //противник найден
  while(distFA>0 && distFB>0){
    //ехать вперед

  };

  //противник ушел влево
  while(distFA>0 && distFB<=0){
    //поворачивать влево

  };

  //противник ушел вправо
  while(distFA<=0 && distFB>0){
    //поворачивать вправо

  };

  //вывод расстояния в консоль
  Serial.println("{");
  Serial.print(distFA);
  Serial.print("} {");
  Serial.print(distFB);
  Serial.print("}");
  
  //задержка для корректной работы датчиков
  delay(100);
}

void yield(){


}
