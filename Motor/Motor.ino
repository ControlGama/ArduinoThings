
//Analógico A0 en 0 conectado al potenciómetro 
int potPin  =  0;

//Pin 11 conectado a la base del transistor
int transistorPin =  8 ;

//Valor devuelto por el potenciómetro 
int potValue  =  0;

void setup()
{
  //  set  the transistor pin as output: 
  pinMode(transistorPin, OUTPUT);
  Serial.begin(9600); 
}

void loop()
{
  
  // Leer el potenciometro,
  //Se necesita dividir entre 4 ya que el valor de retorno 
  // va de 0 a 1023 pero el valor que necesitamos debe de ser 
  // de  0 a 255: 
  potValue = analogRead(potPin) / 4; 
  Serial.print('\n');
   Serial.print(potValue);
    
  //Utilizamos el valor devuelto para controlar la velocidad 
  //del motor a través del transistor:
  analogWrite(transistorPin, potValue); 
  Serial.print('\n');
  
}
