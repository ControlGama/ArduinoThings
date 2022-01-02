int latchPin = 8;  //Pin connected to Pin 12 of 74HC595 (Latch)
int clockPin = 12; //Pin connected to Pin 11 of 74HC595 (Clock)
int dataPin = 11;  //Pin connected to Pin 14 of 74HC595 (Data)

void setup() {
    //set pins to output
  pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void loop() {
  
    for (int i = 0; i < 255; i++) {                         //count from 0 to 255
      
      digitalWrite(latchPin, LOW);                     //set latchPin low to allow data flow
      shiftOut(i);       // shift out first 8 bits
      shiftOut(255-i); // shiftOut second 8 bits//set latchPin to high to lock and send data
      digitalWrite(latchPin, HIGH);
      delay(250);
    }
}

void shiftOut( byte dataOut) { 
  // Shift out 8 bits LSB first, 
  // on rising edge of clock 
  boolean pinState;
  //clear shift register read for sending data
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  // for each bit in dataOut send out a bit
  for (int i = 0; i <= 7; i++) {
    //set clockPin to LOW prior to sending bit
    digitalWrite(clockPin, LOW);
    // if the value of DataOut and (logical AND) a bitmask
    // are true, set pinState to 1 (HIGH)
    if ( dataOut & (1<<i) ) {
      pinState = HIGH;
    }else{
      pinState = LOW;
    }
    
    digitalWrite(dataPin, pinState);
    
    digitalWrite(clockPin,HIGH);
    digitalWrite(dataPin,LOW);    
    }
  
    digitalWrite (clockPin, LOW );
  
}
  
  
  
  
  
  
  
  
