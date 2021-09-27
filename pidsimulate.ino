#define PWM_R 5
#define DIR_R 4

#define HALLSEN_A 2
#define HALLSEN_B 3

int delta_rad=0;
int last_rad=0;
int rad=0;
int motorPwm=0;
int encoderValue=0;
int data=0;
float motorSpeed=0;
float pid_kp;
float pid_ki;
float pid_kd;

float ki;
float k1;
float k2;

int sp;
int error=0;
int last_error=0;
int sum_error=0;

bool signalA = false;
bool signalB = false;


void setup() {
  Serial.begin(9600);

  encoderValue=0;

  sp=200;

  ki=0.06;
  k1=5;
  k2=5;

  pid_kp=4;
  pid_ki=0.05;
  pid_kd=0.02;
}

void loop() {
  while(data<200)
  {
    rad = encoderValue*0.1;
    error = sp - rad;
    sum_error=sum_error * error;
    delta_rad=rad-last_rad;
    //motorSpeed = (ki*sum_error)-((k1*rad)+(k2*delta_rad));
    motorSpeed = (pid_kp*error)+(pid_ki*sum_error)+(pid_kd*(error-last_error));
    last_rad = rad;
    last_error=error;

    if(motorSpeed > 250) motorSpeed =250;
    if(motorSpeed < -250) motorSpeed =-250;

    Serial.print(rad);
    Serial.print(",");
    Serial.print(sp);
    Serial.println();

    data++;
    }
}
