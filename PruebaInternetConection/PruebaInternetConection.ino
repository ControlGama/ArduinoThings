#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial){  
  }
  mySerial.begin(9600);
  
  //modem_init();
  //data_init();
  //internet_init();
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

//---------------------------------------------------------
void modem_init()
{
  Serial.println("Please wait.....");
  mySerial.println("AT");
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
}
void data_init()
{
  Serial.println("Please wait.....");
  mySerial.println("AT");
  delay(1000); delay(1000);
  mySerial.println("AT+CPIN?");
  delay(1000); delay(1000);
  mySerial.print("AT+SAPBR=3,1");
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("contype");
  mySerial.write('"');
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("GPRS");
  mySerial.write('"');
  mySerial.write(0x0d);
  mySerial.write(0x0a);
  delay(1000); ;
  mySerial.print("AT+SAPBR=3,1");
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("APN");
  mySerial.write('"');
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("web.iusacellgsm.mx"); //APN Here
  mySerial.write('"');
  mySerial.write(0x0d);
  mySerial.write(0x0a);
  delay(1000);
  mySerial.print("AT+SAPBR=3,1");
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("USER");
  mySerial.write('"');
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("Iusacellgsm");
  mySerial.write('"');
  mySerial.write(0x0d);
  mySerial.write(0x0a);
  delay(1000);
  mySerial.print("AT+SAPBR=3,1");
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("PWD");
  mySerial.write('"');
  mySerial.write(',');
  mySerial.write('"');
  mySerial.print("iusacellgsm");
  mySerial.write('"');
  mySerial.write(0x0d);
  mySerial.write(0x0a);
  delay(2000);
  mySerial.print("AT+SAPBR=1,1");
  mySerial.write(0x0d);
  mySerial.write(0x0a);
  delay(3000);
}
void internet_init()
{
  Serial.println("Please wait.....");
  delay(1000);
  mySerial.println("AT+HTTPINIT");
  delay(1000); delay(1000);
  mySerial.print("AT+HTTPPARA=");
  mySerial.print('"');
  mySerial.print("CID");
  mySerial.print('"');
  mySerial.print(',');
  mySerial.println('1');
  delay(1000);
}
/*
void Send_data()
{
  gsm.print("AT+HTTPPARA=");
  gsm.print('"');
  gsm.print("URL");
  gsm.print('"');
  gsm.print(',');
  gsm.print('"');
  gsm.print("https:");
  gsm.print('/');
  gsm.print('/');
  
  gsm.print("api.thingspeak.com/update?api_key=xxxxxxxxxxxxxxxxx&field1=");
///xxx is the api key
  gsm.print(temp); //>>>>>>  variable 1 (temperature)
  gsm.print("&field2=");
  gsm.print(humi); //>>>>>> variable 2 (Humidity)
  gsm.print('"');
  gsm.write(0x0d);
  gsm.write(0x0a);
  delay(1000);
  gsm.println("AT+HTTPACTION=0");
  delay(1000);
} */
