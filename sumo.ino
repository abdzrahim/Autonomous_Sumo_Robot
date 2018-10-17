 /*
This program for autonomous sumo robot.
This program made by JAZARI club(UTM).
Using 4 ir sensor trcrt5000.
And 3 Sonar Sensor
*/
#include <SoftwareSerial.h>

#define SABER_TX_PIN  1
//Not used but still initialised, Digital pin 12 is serial receive from Sabertooth
#define SABER_RX_PIN  0

//set baudrate to match sabertooth dip settings
#define SABER_BAUDRATE 9600

//simplifierd serial limits for each motor
#define SABER_MOTOR1_FULL_FORWARD 127
#define SABER_MOTOR1_FULL_REVERSE 1

#define SABER_MOTOR2_FULL_FORWARD 255
#define SABER_MOTOR2_FULL_REVERSE 128

//motor level to send when issuing full stop command
#define SABER_ALL_STOP  0


const int led4 = 2;
const int led3 = 3;
const int led2 = 4;
const int led1 = 5;
int ir1 = A0; int ir2 = A1;
int ir3 = A2; int ir4 = A3;
//sonar sensor
#define trigPin 13
#define echoPin 12
#define trigPin1 11
#define echoPin1 10
#define trigPin2 7
#define echoPin2 6

int val[4]; // val[0]=ir1 // val[1]=ir2 // val[2]=ir3 //val[3]=ir4
int son[3];
int dur;
int dur1;
int dur2;
int trace;
void monitorprint(void);
void monitor_print(void);
//irsensor
void irread(void);
void checkir(void);
//sonarsensor
void sonarread(void);;
void checksonar(void);
void led_low(void);
void led_high(void);
const int X = 300; //kanan sonarsensor
const int C = 420; //center sonar 
const int V = 300; //kiri sonar sensor
const int A = 200; //irsensor kanan depan //change this one
const int S = 500; //irsensor kiri depan
const int D = 500; //irsensor kiri belakang
const int F = 500;//irsensor kanan belakang
const int f = 60; //speed full forward
const int h = 30; //speed half forward
SoftwareSerial SaberSerial = SoftwareSerial (SABER_RX_PIN, SABER_TX_PIN );




void setup()                    // run once, when the sketch starts
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  //ir sensor
  pinMode(ir1, INPUT);            //set sensePin as input
  pinMode(ir2, INPUT);            //set sensePin as input
  pinMode(ir3, INPUT);            //set sensePin as input
  pinMode(ir4, INPUT);            //set sensePin as input

  //sonar sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);      // HARD wired Serial feedback to PC for debugging in Wiring
  initSabertooth();
}


void loop ()
{
  initialization();
  //monitor_print();
   delay(5);
    led_high();
    motor_right(63,63);
    delay(400);
    motor_forward(40,63);
    delay(1700);
    motor_left(63,63);
    delay(500);
    led_low();
  while (1)
  {
    ir_read();
    sonar_read();
    check_sonar_ir_2();
  } 

}
void ir_read(void) {
  val[0] = analogRead (A0);
  val[1] = analogRead (A1);
  val[2] = analogRead (A2);
  val[3] = analogRead (A3);
}

void sonar_read(void) {
//  //sonar1
//  digitalWrite(trigPin, LOW);  // Added this line
//  delayMicroseconds(2); // Added this line
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10); // Added this line
//  digitalWrite(trigPin, LOW);
//  dur = pulseIn(echoPin, HIGH);
//  son[0] = (dur / 2) / 2.91;
  //sonar2
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  dur1 = pulseIn(echoPin1, HIGH);
  son[1] = (dur1 / 2) / 2.91;
//  //sonar3
//  digitalWrite(trigPin2, LOW);  // Added this line
//  delayMicroseconds(2); // Added this line
//  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(10); // Added this line
//  digitalWrite(trigPin2, LOW);
//  dur2 = pulseIn(echoPin2, HIGH);
//  son[2] = (dur2 / 2) / 2.91;
}
void initSabertooth (void)
{
  pinMode ( SABER_TX_PIN, OUTPUT );
  SaberSerial.begin( SABER_BAUDRATE );
  Serial.write(64);
  Serial.write(192);
}

void initialization()
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  Serial.write(64);
  Serial.write(192);
}
void check_sonar_ir_2(void) {
  if (val[0] > A) //ir1 active
  {
    led_high();
    motor_backward(50, 30);
    delay(200);
  }
  else if  (val[1] > S) //ir2 active
  {
    led_high();
    motor_backward(30, 50);
    delay(200);
  }
  else if  (val[2] > D) //ir3 active
  {
    led_high();
    motor_forward(50, 30);
    delay(200);
  }
  else if  (val[3] > F) //ir4 active
  {
    led_high();
    motor_forward(30, 50);
    delay(200);
  }  
  else if (son[1]<=C)
  {
    digitalWrite(led3, HIGH);
    motor_forward(f, f);
    //monitorprint();
  } 
//  else if ((son[0] >= X) && (son[1] >= C) && (son[2] <= X)) //sonar3 active      //001
//  {
//    digitalWrite(led2, HIGH);
//    motor_right(f, f);
//    //monitorprint();
//    //trace=2;
//  }
//  else if ((son[0] >= X) && (son[1] <= C) && (son[2] >= X)) //sonar2 active      //010
//  {
//    digitalWrite(led3, HIGH);
//    motor_forward(f, f);
//    //monitorprint();
//    
//  }
//  else if ((son[0] <= X) && (son[1] >= C) && (son[2] >= X)) //sonar1 active      //100
//  {
//    digitalWrite(led4, HIGH);
//    motor_left(f, f);
//    //monitorprint();
//    //trace=3;
//  }
  else
  {
    led_low();
    motor_left(25,15);
    //delay(15);
    //motor_forward(10,5);
    //delay(5);
    //motor_stop();
    //memory();
  }
}
// (motor kanan, motor kiri)
void motor_forward(unsigned char l, unsigned char r)
{
  Serial.write(64 - r);   // 127
  Serial.write(192 + l);   // 255
}
void motor_backward(unsigned char l, unsigned char r)
{
  Serial.write(64 + r);   // 127
  Serial.write(192 - l);   // 255
}
void motor_right(unsigned char l, unsigned char r)
{
  Serial.write(64 + r);   // 127
  Serial.write(192 + l);   // 255
}
void motor_left(unsigned char l, unsigned char r)
{
  Serial.write(64 - r);   // 127
  Serial.write(192 - l);   // 255
}
void motor_stop()
{
  Serial.write(64);
  Serial.write(192);
}
void led_low(void)
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}
void led_high(void)
{ digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
}
void monitor_print(void) {
  ir_read();
  sonar_read();
  Serial.print(val[0]);
  Serial.print("\t");
  Serial.print(val[1]);
  Serial.print("\t");
  Serial.print(val[2]);
  Serial.print("\t");
  Serial.print(val[3]);

//turn off sensor kiri
//  Serial.print("\t");
//  Serial.print("r="); //right
//  Serial.print(son[0]);

  Serial.print("\t");
  Serial.print("c="); //centre
  Serial.print(son[1]);

//turn off sensor kanan
//  Serial.print("\t");
//  Serial.print("l="); //left
//  Serial.print(son[2]);
  Serial.println("\n");
  delay(5);
}
void memory(void)
{
    switch(trace)
    {
        case 1: motor_forward(20,20);break;
        case 2: motor_right(10,10);break;
        case 3: motor_left(10,10);break;
    }

}
