#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define MOT_LEFT 5
#define MOT_RIGHT 6
#define RES_SPEED A0
#define RES_ROTATE A1
#define COEF 3
unsigned int Speed;
int dx;
int speed_left , speed_right;

RF24 radio(9,10); // "создать" модуль на пинах 9 и 10 Для Уно

byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб
int recieved_data[2];

void setup(){
  pinMode(MOT_LEFT, OUTPUT);
  pinMode(MOT_RIGHT , OUTPUT);
  
  pinMode(RES_SPEED , INPUT);
  pinMode(RES_ROTATE , INPUT);
  
  Serial.begin(9600); //открываем порт для связи с ПК
  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openReadingPipe(1,address[0]);      //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  
  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}

void loop() {
    byte pipeNo;
    byte gotByte;                          
    while( radio.available(&pipeNo)){    // слушаем эфир со всех труб
      radio.read( &recieved_data , sizeof(recieved_data) );         // чиатем входящий сигнал
   }
    Speed = recieved_data[0];
    dx = recieved_data[1];
    constrain(Speed , 0 , 255);
    constrain(dx , -128 , 127);
    constrain(speed_left , 0 , 255);
    constrain(speed_right , 0 , 255);
    speed_left = getLeftSpeed(Speed , dx , COEF);
    speed_right = getRightSpeed(Speed , dx , COEF);
    
    analogWrite(MOT_LEFT , speed_left);
    analogWrite(MOT_RIGHT , speed_right);
    
    Serial.print("dx:");Serial.print(dx);Serial.print("\tSpeed left motor:");Serial.print(Speed); Serial.print("\tspeed right motor:");  Serial.println(speed_right);
}

 int getLeftSpeed(int Speed , int dx , int coef){
    if(dx < -5) return (Speed + ((dx) / coef));
    else return Speed;
 }
    
  int getRightSpeed(int Speed, int dx , int coef){
    if(dx > 5) return (Speed - ((dx) / coef));
    else return Speed ;
    }
