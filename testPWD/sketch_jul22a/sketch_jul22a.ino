#include <time.h>
#define TIME 1000
#define VOL A0
#define LED 3
unsigned long myTime = 0;
unsigned int pwm;
void setup() {
  pinMode(VOL , INPUT);
  pinMode(LED , OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(millis()- myTime > TIME){
    myTime = millis();
    Serial.print("Value:");
    Serial.println(analogRead(VOL));
  }
    pwm = analogRead(VOL);
    pwm = map(pwm, 0, 1023, 0, 255);
    constrain(pwm , 0 , 255);
    analogWrite(LED , pwm );
}
