const char* sensor[]={ 1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1 };
int i=0;
float gigsxp;
float gigsy;
float gigsd;
//==================//
float kpx = 1.0;//8.0; //feedback tertinggi
float kix = 10.0; // feedback error dari tertinggi
float kdx = 1.8; // feedback penghalus
float imaxx = 200.0;//kecepatan timer pid
float tix = 25.0;//20
float out_px=0,out_ix=0,out_dx=0;
float errorx=0,integralx=0,last_errorx=0,spx=0,pvx=0;
//pid tumit
int kx=0;
int ky=0;
int kd=0;
//tumit kanan kiri
float kpy = 5.0;
float kiy = 20.0;
float kdy = 2.60;
float imaxy = 200.0;
float tiy = 25.0;
float out_py=0,out_iy=0,out_dy=0;
float errory=0,integraly=0,last_errory=0,spy=0,pvy=0;

float kpd = 0.5;
float kid = 10.0;
float kdd = 0.6;
float imaxd = 200.0;
float tid = 25.0;
float out_pd=0,out_id=0,out_dd=0;
float errord=0,integrald=0,last_errord=0,spd=0,pvd=0;
//tumit
int data;
float sp = 512;
float setpoint = 2048;

float outpidx = 0;//hasil tumit
float outpidd = 0;//hasil dengkul
float outpidy = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
float gigsxp=0;
float gigsxm=0;
float gigsy=0;
float gigsd=0;
}

void loop() {
  while(i<350){
  for (i=0; i<=350; i++){ 
  //Serial.println(int(users[i]));
  data = int(sensor[i]);
  //Serial.print(data);
  
kx=data;
ky=data;
kd=data;
pvx=0-kx;
pvd=0-kd;
pvy=0-ky;
errorx=spx-pvx;
errory=spy-pvy;
errord=spd-pvd;
out_px=(float)errorx*kpx;
out_pd=(float)errord*kpd;
out_py=(float)errory*kpy;
out_ix=(float)(integralx*kix)/tix;
out_iy=(float)(integraly*kiy)/tiy;
out_id=(float)(integrald*kid)/tid;
if( errorx !=0 ) integralx=integralx+errorx;
else integralx=0;
if( errory !=0 ) integraly=integraly+errory;
else integraly=0;
if( errord !=0 ) integrald=integrald+errord;
else integrald=0;
if(out_ix>imaxx)out_ix=imaxx;
if(out_iy>imaxy)out_iy=imaxy;
if(out_id>imaxd)out_id=imaxd;
if(out_ix<-imaxx)out_ix=-imaxx;
if(out_iy<-imaxy)out_iy=-imaxy;
if(out_id<-imaxd)out_id=-imaxd;
out_dx=(float)(errorx-last_errorx)*kdx;
out_dy=(float)(errory-last_errory)*kdy;
out_dd=(float)(errord-last_errord)*kdd;
last_errorx=errorx;
last_errory=errory;
last_errord=errord;
//if(outpidx > 100) outpidx = 100;
//if(outpidy > 100) outpidy = 100;
//if(outpidd > 100) outpidd = 100;
//if(outpidx < -200) outpidx = -200;
//if(outpidy < -200) outpidy = -200;
//if(outpidd < -200) outpidd = -200;
outpidx=out_px+out_ix+out_dx;
outpidy=out_py+out_iy+out_dy;
outpidd=out_pd+out_id+out_dd; 
gigsxp=setpoint-outpidx;
gigsy=setpoint-outpidy;
gigsd=setpoint-outpidd;


Serial.print(round(gigsxp));
Serial.print(",");
Serial.print(round(gigsy));
Serial.print(",");
Serial.print(round(gigsd));
Serial.print(",");
Serial.println(round(setpoint));
  }
  
  }
}
