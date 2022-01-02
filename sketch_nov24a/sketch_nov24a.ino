#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop()
{
  
  if (Serial.available()>0)
  Serial.println("Test"); // AT Command to receive a live SMS
   switch(Serial.read())
  {
    case 's':
      Serial.println("Esto es S"); 
      SendMessage();
      break;
    case 'r':
      Serial.println("Esto es r"); 
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  
  //mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  mySerial.println("AT+CMGS=\"+528111315096\"\r"); // Jaciel
  //mySerial.println("AT+CMGS=\"+528118895387\"\r"); // Mio
  
  delay(1000);
  mySerial.println("Si te llega este mensaje manda whats 2");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 
