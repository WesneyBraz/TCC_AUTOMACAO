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
if (k<=500){
  velocidade = 35;
  }
   if (k>500){
    velocidade = 50;
    }
   if (k > 1000){
    velocidade = 200;
    }
   if (k > 1500){
   velocidade = 50;
    }
   if (k > 2000){
   velocidade = 35;
    }
       if (k > 2500){
   velocidade = 10;
    }//////////////////
   

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
//Serial.print("\t"); 
//Serial.println(k);
   
holdingRegs[RPM]=rpm;
//holdingRegs[MOTOR] = holdingRegs[ELIPSE1];
//analogWrite(10, holdingRegs[MOTOR]);
}
