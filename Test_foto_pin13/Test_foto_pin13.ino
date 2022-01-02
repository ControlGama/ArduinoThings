int foto = 7;
bool on_off;
bool imprime;

void setup() {
  // put your setup code here, to run once:
  pinMode(foto, INPUT);
  Serial.begin(9600);
  on_off = LOW;
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    Serial.write(on_off);
    Serial.write("\n entro");
    on_off = LOW;
    Serial.write(on_off);
    Serial.write("\n cambio");
    delay(2000);
  }
  
  digitalWrite(foto,on_off);
  imprime = digitalRead(foto);
  if (imprime==HIGH){
    Serial.write("\n on"); 
  }else{
    Serial.write("\n off"); 
  }
  
  delay(2000);
      
}
