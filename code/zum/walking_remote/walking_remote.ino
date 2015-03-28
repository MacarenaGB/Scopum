#include <Servo.h> 
#define MAX_CH 2

Servo sRR; //roll right
Servo sRL; //roll left
Servo sYR; //yaw right                       
Servo sYL; //yaw left

const int LDR = A2;    // the number of sensor pin
int ldr; //valuo of ldr

int channel[MAX_CH];

int offset_RR=0; //Zero point calibration
int offset_RL=0;
int offset_YR=0;
int offset_YL=0;

int time=500; //Walking parameters
int amp_roll=25;
int amp_yaw=15;


void setup() {
  Serial.begin(19200);
  sRR.attach(9);
  sRL.attach(8);
  sYR.attach(7);
  sYL.attach(6);
  channel[0]=90;
  channel[1]=90; 
  
  pinMode(LDR, INPUT);
  
  sRR.write(90+offset_RR);
  sRL.write(90+offset_RL);
  sYR.write(90+offset_YR);
  sYL.write(90+offset_YL);
  
}

void loop() {
 if(Serial.available()>MAX_CH*2-1){
    while(Serial.read()!=0);
    for (int i=0;i<MAX_CH;i++) 
      channel[i]=((int)Serial.read());
   ldr=analogRead(LDR);
   Serial.println(ldr);   
   if(ldr>250){ 
     sRR.write((channel[0]+45+offset_RR)+amp_roll);  
     sRL.write((channel[0]+45+offset_RL)+amp_roll);
     sYR.write((channel[0]+45+offset_YR)+amp_yaw);  
     sYL.write((channel[0]+45+offset_YL)+amp_yaw);   
     delay(time);  
     
     sRR.write((channel[0]+45+offset_RR)+amp_roll);  
     sRL.write((channel[0]+45+offset_RL)+amp_roll);
     sYR.write((channel[0]+45+offset_YR)-amp_yaw);  
     sYL.write((channel[0]+45+offset_YL)-amp_yaw);   
     delay(time);
     
     sRR.write((channel[0]+45+offset_RR)-amp_roll);  
     sRL.write((channel[0]+45+offset_RL)-amp_roll);
     sYR.write((channel[0]+45+offset_YR)-amp_yaw);  
     sYL.write((channel[0]+45+offset_YL)-amp_yaw);   
     delay(time);  
     
     sRR.write((channel[0]+45+offset_RR)-amp_roll);  
     sRL.write((channel[0]+45+offset_RL)-amp_roll);
     sYR.write((channel[0]+45+offset_YR)+amp_yaw);  
     sYL.write((channel[0]+45+offset_YL)+amp_yaw);   
     delay(time); 
     }
     else if(ldr<=250)
     {
      sRR.write(90+offset_RR);
      sRL.write(90+offset_RL);
      sYR.write(90+offset_YR);
      sYL.write(90+offset_YL);
     }
     
   }
}


