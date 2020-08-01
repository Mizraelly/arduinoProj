/*
 Дана програма 
*/
#define LED 5
#define BUTTON 8
#define WAIT_TIME_BOOST 200
bool but  , but_flag ; // but_flag - флажок , для того щоб виконувалась фу
unsigned long last_pressed , boost_timer , last_pressed_boost = 0;
unsigned int count = 0;

void setup() {
  pinMode(LED , OUTPUT);
  pinMode(BUTTON , INPUT_PULLUP);
 
  Serial.begin(9600);
}

void loop() {
  but = !digitalRead(BUTTON);
  led_on(but , but_flag, last_pressed , count);
  turbo_boost(but , but_flag , last_pressed , last_pressed_boost , count);
  led_off(but , but_flag , count);
}

//Functions...
void led_on(bool but , bool & but_flag , unsigned long & last_pressed , unsigned int & count){
  if(but == 1 && but_flag == 0 && millis() - last_pressed > 100) { 
    digitalWrite(LED , HIGH);
    Serial.println("butt pressed");
    but_flag = 1;
    ++count;
    last_pressed = millis();
    }
}
    
  void turbo_boost(bool but , bool but_flag , unsigned long last_pressed , unsigned long & last_pressed_boost , unsigned int & count){
    if(but == 1 && but_flag == 1 && millis() - last_pressed > 2000){
      if(millis() - last_pressed_boost > WAIT_TIME_BOOST){
        Serial.println("load func. turbo_boost");
        count ++;
        last_pressed_boost = millis();
      }
    }
  }
  void led_off(bool but , bool & but_flag , unsigned int count){
  if (but == 0 && but_flag == 1){ 
    digitalWrite(LED , LOW);
    Serial.print("butt released!\ncount:");
    Serial.println(count);
    but_flag = 0;
    }
  }
  
  
