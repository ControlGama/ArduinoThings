#include <Servo.h>

int sencorPir1 = 2;
int sencorPir2 = 3;
int indicadorBat = 13;
//int sencorPir3 = 4;
//int sencorPir4 = 5;
int foto = 7; 

Servo motor1;

void setup()
{
  pinMode(sencorPir1, INPUT);
  pinMode(sencorPir2, INPUT);
  pinMode(indicadorBat, OUTPUT);
  //pinMode(sencorPir3, INPUT);
  //pinMode(sencorPir4, INPUT);
  pinMode(foto, INPUT);  
  Serial.begin(9600);
  motor1.attach(6);
  Serial.println("Posicion origen");
  motor1.write(90);
}

void loop()
{
  if(digitalRead(sencorPir1)==HIGH) {
    Serial.println("Righ");
    motor1.write(180);
    Serial.println("esperando 2 seg");
    delay(2000);
    digitalWrite(foto,HIGH);
    Serial.println("esperando 2 seg +");
    Serial.println("Camara On");
    delay(2000);
    digitalWrite(foto,LOW);
    Serial.println("esperando 2 seg ++");
    Serial.println("Camara off");
    delay(2000);
    Serial.println("Posicion origen");
    motor1.write(90);
  }

  if(digitalRead(sencorPir2)==HIGH) {
    Serial.println("left");
    motor1.write(0);
    Serial.println("esperando 2 seg");
    delay(2000);
    digitalWrite(foto,HIGH);
    Serial.println("esperando 2 seg +");
    Serial.println("Camara On");
    delay(2000);
    digitalWrite(foto,LOW);
    Serial.println("esperando 2 seg ++");
    Serial.println("Camara off");
    delay(2000);
    Serial.println("Posicion origen");
    motor1.write(90);
  }  

  //Monitor Voltaje
  int SensorValue = analogRead(A0);
  float voltaje = SensorValue * ( 5.00 / 1023.00 ) * 3;
 
  Serial.println(voltaje);
  
  if (voltaje <= 5){
    
    // ENCENDER LED
    digitalWrite(indicadorBat, HIGH);
    delay(2000);
    digitalWrite(indicadorBat, LOW);
    delay(2000);
    
  } 

/*
  if(digitalRead(sencorPir3)==HIGH) {
    Serial.println("Algo se movio Sup Izq");
    motor1.write(45);
    delay(2000);
    digitalWrite(foto,HIGH);
    delay(2000);
    digitalWrite(foto,LOW);
    delay(2000);

    motor1.write(90);
  }  
  
  if(digitalRead(sencorPir4)==HIGH) {
    Serial.println("Algo se movio Inf Izq");
    motor1.write(0);
    delay(2000);
    digitalWrite(foto,HIGH);
    delay(2000);
    digitalWrite(foto,LOW);
    delay(2000);
    motor1.write(90);
  }
*/
}
