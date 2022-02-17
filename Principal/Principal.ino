/*
Diseñador: Cristian Rendon Rodriguez
Codigo: 1001506044 
Archivo: C:\Users\CRISTIAN\Desktop\Carpetas\Universidad\Semestre 8\Electronica Digital\Proyecto Pif
Fecha inicio: 12/02/2022
Fecha fin: 19/02/2022
Version: 1.0
Descripcion: Coger el módulo de arduino 1, 1 sensor temperatura, 3 motores DC, 3 teclado, un display de 2x16, y 1 sensor de ultrasonido'
*/


#include <LiquidCrystal.h>//incluimos la libreria del display

LiquidCrystal lcd(2,3,4,5,6,7);//conexiones(rs,enable,d4,d5,d6,d7)

int Boton1 = A0;
int Boton2 = A1;
int Boton3 = A2;
int pinMotor13 = 13;
int pinMotor12 = 12;
int pinMotor8 = 8;
long Duracion;
long Distancia;
int echo = 1;
int trigger = 0;
int val; 
void setup() {

 /* lcd.setCursor(0,0);//colocamos el cursor en la columna 0 fila 0
  lcd.print("Hola a todos");//imprimimos texto
  lcd.setCursor(0,1);//colocamos el cursor en la columna 0 fila 1
  lcd.print("Que esten Bien :)");//imprimimos texto
  */
  lcd.begin(16,2);//iniciamos la interfa
  lcd.clear();//Limíaños la pantalla
  pinMode(Boton1,INPUT); //ENTRADA
  pinMode(Boton2,INPUT); //ENTRADA
  pinMode(Boton3,INPUT); //ENTRADA
  pinMode(pinMotor13,OUTPUT); //SALIDA
  pinMode(pinMotor12,OUTPUT); //SALIDA
  pinMode(pinMotor8,OUTPUT); //SALIDA
  pinMode(trigger,OUTPUT);//SALIDA
  pinMode(echo,INPUT);//ENTRADA
  pinMode(A3,INPUT);//ENTRADA
  pinMode(11,OUTPUT);//SALIDA
  pinMode(10,OUTPUT);//SALIDA

}

void loop() {
  lcd.clear();//Limíaños la pantalla
  digitalWrite(trigger,LOW);//para estabilizar el modulo ultrasonico
  delayMicroseconds(4);
  if(digitalRead(Boton1) == HIGH){ //abierto circuito 
    FuncionBotton1(1);
  }else if(digitalRead(Boton1) == LOW){ //cerrado circuito
    FuncionBotton1(0);
    if(digitalRead(Boton2) == LOW){
     
      FuncionBotton2();
    }
  }
  if(digitalRead(Boton3) == LOW){ //cerrado circuito
      Temperatura();
  }
  
 
  digitalWrite(pinMotor13,LOW);
  digitalWrite(pinMotor12,LOW);
  digitalWrite(pinMotor8, LOW);
delay(1000);
}

void FuncionBotton1(int data){
  lcd.setCursor(0,0);//colocamos el cursor en la columna 0 fila 0
  //lcd.setCursor(0,1);//colocamos el cursor en la columna 0 fila 1
  if(data == 1)
  {
    lcd.print("Abriendo Caja");//imprimimos texto
    digitalWrite(pinMotor13, HIGH);//activo pin 13
    digitalWrite(pinMotor12,LOW);//desactivo pin 12
    delay(1500);
    lcd.clear();//Limíaños la pantalla
    lcd.print("Abierta");//imprimimos 
    disparo(0);
  }
  else if(data == 0)
  {
    lcd.print("Cerrando Caja");//imprimimos texto
    digitalWrite(pinMotor13,LOW);//desactivo pin 13
    digitalWrite(pinMotor12,HIGH);//activo pin 12
    delay(1500);
    lcd.clear();//Limíaños la pantalla
    lcd.print("Cerrada");//imprimimos 
    disparo(65);
  }  
}

void disparo(int numero){
  lcd.setCursor(0,1);//colocamos el cursor en la columna 0 fila 1
  digitalWrite(trigger,LOW);//para estabilizar el modulo ultrasonico
  delayMicroseconds(4);
  digitalWrite(trigger,HIGH);//Disparo de un pulso en trigger de longitud 10
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  Duracion = pulseIn(echo,HIGH);//Lectura de la duracion del pulso HIGH 
  Distancia = Duracion/58.4;// calculo distancia (cm)
  lcd.print("distancia:");//imprimimos 
  lcd.print(Distancia-numero);
}

void FuncionBotton2(){
   delay(1500);
   lcd.clear();   
   lcd.setCursor(0,0);//colocamos el cursor en la columna 0 fila 1
   lcd.print("Motores");//imprimimos 
   lcd.setCursor(0,1);//colocamos el cursor en la columna 0 fila 1
   lcd.print("Encendidos :)");//imprimimos 
  digitalWrite(pinMotor8, HIGH);
  delay(4000);
}

void Temperatura(){
   val = analogRead(A3); //realiza la lectura del pin 9 sensor de temperatura
   float mv = (val/1024.0)*5000; 
   float temp = mv/10; //obtenemos la temperatura
   lcd.clear();   
   lcd.setCursor(0,0);//colocamos el cursor en la columna 0 fila 1
   lcd.print("Temperatura");//imprimimos 
   //lcd.print(val);
   lcd.setCursor(0,1);//colocamos el cursor en la columna 0 fila 1
   lcd.print(temp);//imprimimos 
   lcd.print(" Grados");//imprimimos 
   if(temp >37.6){
    digitalWrite(11,LOW);
     digitalWrite(10,HIGH);
   }else if(temp < 37.6){
    digitalWrite(10,LOW);
     digitalWrite(11,HIGH);
   }

  delay(1000);
}

 
