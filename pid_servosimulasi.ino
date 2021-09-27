#include <Servo.h>
Servo myservo;

int sp = 90;

float kp = 1.28;
float ki = 0.67;
float kd = 0.15;

float p,i,d,suhu,pid,pidx;
float error,errorx,sumerr;
long duration, distance;

void setup() {
  myservo.attach(9);
  Serial.begin (9600);
 // myservo.write(90);
  }

void loop() {
  distance=30;
  error = sp - distance;
  p = error * kp;
  sumerr = error + errorx;
  i = ki * sumerr;
  d = error - errorx;
  pid = p + i + d;
  pid = 250.0 - pid;
 
  pidx = sp - pid;
 
  myservo.write(pidx);

  if(pidx < 1){
  pidx = 0;
  }
 
  if(pidx > 250){
  pidx = 250;
  }

  Serial.print(distance);
  Serial.print(" ");
  Serial.println(pidx);
  delay(2000);

 errorx = error;
//myservo.write(0);
}
