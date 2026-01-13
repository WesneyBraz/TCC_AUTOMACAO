#include <SimpleModbusSlave.h>
#define sensor 7

int estado=0;
int cont=0;
int rpm;
int rpm1,rpm2,rpm3,rpm4,rpm5;
int k=0;
int valor=0;

unsigned long temp1 = 0;
int IN1 = 8 ;
int IN2 = 9 ;
int pwm = 10;
int velocidade = 35;

enum 
{ 
 
  RPM,
  PWM,
  ELIPSE,
  MOTOR,
  ELIPSE1,         
  HOLDING_REGS_SIZE 
};
unsigned int holdingRegs[HOLDING_REGS_SIZE]; 
////////////////////////////////////////////////////////////

void setup() {
modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
modbus_update_comms(9600, SERIAL_8N1, 1);

pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(pwm,OUTPUT);
pinMode(sensor, INPUT);
Serial.begin(9600);
}

void loop() {
modbus_update();
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(pwm,velocidade);

//velocidade 
k = k +1 ;
if (k<=250){
  velocidade = 35;
  }
   if (k>500){
    velocidade = 40;
    }
   if (k >= 750){
    velocidade = 45;
    }
   if (k >= 1000){
   velocidade = 50;
    }//////////////////
    if (k >= 1250){
   velocidade = 55;
    }
    if (k > 1500){
   velocidade = 60;
    }
    if (k > 1750){
   velocidade = 65;
    }
    if (k > 2000){
   velocidade = 70;
    }//////////////////
    if (k > 2250){
   velocidade = 75;
    }
    if (k > 2500){
   velocidade = 80;
    }
    if (k > 2750){
   velocidade = 85;
    }
    if (k > 3000){
   velocidade = 90;
    }////////////////////
    if (k > 3250){
   velocidade = 95;
    }
    if (k > 3500){
   velocidade = 100;
    }
    if (k > 3750){
   velocidade = 105;
    }
    if (k > 4000){
   velocidade = 110;
    }//////////////////
    if (k > 4250){
   velocidade = 115;
    }
    if (k > 4500){
   velocidade = 120;
    }
    if (k > 4750){
   velocidade = 125;
    }
    if (k > 5000){
   velocidade = 130;
    }////////////////////
    if (k > 5250){
   velocidade = 135;
    }
    if (k > 5500){
   velocidade = 140;
    }
    if (k > 5750){
   velocidade = 145;
    }
    if (k > 6000){
   velocidade = 150;
    }//////////////////
    if (k > 6250){
   velocidade = 155;
    }
    if (k > 6500){
   velocidade = 160;
    }
    if (k > 6750){
   velocidade = 165;
    }
    if (k > 7000){
   velocidade = 170;
    }//////////////////////
    if (k > 7250){
   velocidade = 175;
    }
    if (k > 7500){
   velocidade = 180;
    }
    if (k > 7750){
   velocidade = 185;
    }
    if (k > 8000){
   velocidade = 190;
    }/////////////////////
    if (k > 8250){
   velocidade = 195;
    }
    if (k > 8500){
   velocidade = 200;
    }
    if (k > 8750){
   velocidade = 205;
    }
    if (k > 9000){
   velocidade = 210;
    }///////////////////////
    if (k > 9250){
   velocidade = 215;
    }
    if (k > 9500){
   velocidade = 220;
    }
    if (k > 9750){
   velocidade = 225;
    }
    if (k > 10000){
   velocidade = 230;
    }//////////////////////
    if (k > 10250){
   velocidade = 235;
    }
    if (k > 10500){
   velocidade = 240;
    }
    if (k > 10750){
   velocidade = 245;
    }
    if (k > 11000){
   velocidade = 250;
    }  ////////////////
    if (k > 11250){
   velocidade = 255;
    }      


cont = 0;  
estado = digitalRead(sensor);
temp1 = millis();

//calculo da velocidade   
  while(millis() <= temp1+50){
    estado = digitalRead(sensor);
    if (estado == HIGH){
     cont++;
  
     while(estado == HIGH){
      estado = digitalRead(sensor);
       delayMicroseconds(50); 

      }
    }
  }
  /////
rpm1 =(((cont*60*1.18))*4);

rpm5 = rpm4;
rpm4 = rpm3;
rpm3 = rpm2;
rpm2 = rpm1;
rpm1 = rpm;

rpm = (rpm1 + rpm2 + rpm3 + rpm4 + rpm5)/5;

Serial.print(rpm);
Serial.print("\t"); 
Serial.println(velocidade);
   
holdingRegs[RPM]=rpm;
//holdingRegs[MOTOR] = holdingRegs[ELIPSE1];
//analogWrite(10, holdingRegs[MOTOR]);
}
