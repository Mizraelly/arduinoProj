#define MOT_LEFT 5
#define MOT_RIGHT 6
#define RES_SPEED A0
#define RES_ROTATE A1
#define COEF 3
unsigned int Speed;
int dx;
int speed_left , speed_right;
void setup() {
  pinMode(MOT_LEFT, OUTPUT);
  pinMode(MOT_RIGHT , OUTPUT);
  
  pinMode(RES_SPEED , INPUT);
  pinMode(RES_ROTATE , INPUT);
  
  Serial.begin(9600);
}

void loop() {
  Speed = map(analogRead(RES_SPEED) , 0 , 1023 , 0 , 255);
  dx = map(analogRead(RES_ROTATE) , 0 , 1023 , -128 , 127);
  constrain(Speed , 0 , 255);
  constrain(dx , -128 , 127);
  constrain(speed_left , 0 , 255);
  constrain(speed_right , 0 , 255);
  speed_left = getLeftSpeed(Speed , dx , COEF);
  speed_right = getRightSpeed(Speed , dx , COEF);
  
  analogWrite(MOT_LEFT , speed_left);
  analogWrite(MOT_RIGHT , speed_right);
  
  Serial.print("dx:");Serial.print(dx);Serial.print("\tSpeed left motor:");Serial.print(speed_left); Serial.print("\tspeed right motor:");  Serial.println(speed_right);
}

 int getLeftSpeed(int Speed , int dx , int coef){
    if(dx < -5) return (Speed + ((dx) / coef));
    else return Speed;
 }
    
  int getRightSpeed(int Speed, int dx , int coef){
    if(dx > 5) return (Speed - ((dx) / coef));
    else return Speed ;
    }
