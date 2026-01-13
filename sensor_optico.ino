#include <SimpleModbusSlave.h>
#define sensor 7
#define ledb 2
#define ledg 3
#define ledy 5
#define ledr 6

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
int velocidade = 200 ;

enum 
{ 
 
  RPM,
  MOTOR,
  ELIPSE,         
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
pinMode(ledb,OUTPUT);
pinMode(ledg,OUTPUT);
pinMode(ledy,OUTPUT);
pinMode(ledr,OUTPUT);
Serial.begin(9600);
}

void loop() {
modbus_update();
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(pwm,velocidade);

//velocidade 
/*k = k +1 ;
if (k<=250){
  velocidade = 45;
  }
   if (k>500){
    velocidade = 55;
    }
   if (k >= 750){
    velocidade = 100;
    }
   if (k >= 1000){
   velocidade = 200;
    }
    */
   //////////////////
  

cont = 0;  
estado = digitalRead(sensor);
temp1 = millis();

//calculo da velocidade   
  while(millis() <= temp1+100){
    estado = digitalRead(sensor);
    if (estado == HIGH){
     cont++;
  
     while(estado == HIGH){
      estado = digitalRead(sensor);
       delayMicroseconds(100); 

      }
    }
  }
  /////
rpm1 =(((cont*60*0.61))*4);

rpm5 = rpm4;
rpm4 = rpm3;
rpm3 = rpm2;
rpm2 = rpm1;
rpm1 = rpm;

rpm = (rpm1 + rpm2 + rpm3 + rpm4 + rpm5)/5;

Serial.print(rpm);
Serial.print("\t"); 
Serial.print(velocidade);
Serial.print("\t"); 
Serial.println(temp1);
/////////////blue
if(rpm>1000)
{
  digitalWrite(ledb,HIGH);
}
if(rpm<1000)
{
  digitalWrite(ledb,LOW);
}
/////////////green
   if(rpm>2000)
{
  digitalWrite(ledg,HIGH);
}
if(rpm<2000)
{
  digitalWrite(ledg,LOW);
}
/////////////yellon
   if(rpm>4000)
{
  digitalWrite(ledy,HIGH);
}
if(rpm<4000)
{
  digitalWrite(ledy,LOW);
}
/////////////red
   if(rpm>5000)
{
  digitalWrite(ledr,HIGH);
}
if(rpm<5000)
{
  digitalWrite(ledr,LOW);
}

holdingRegs[RPM]=rpm;
//holdingRegs[MOTOR] = holdingRegs[ELIPSE];
//analogWrite(pwm, holdingRegs[MOTOR]);
//velocidade = holdingRegs[MOTOR];
//analogWrite(pwm,velocidade);
}
