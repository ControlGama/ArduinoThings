int latchPin = 8;  //Pin connected to Pin 12 of 74HC595 (Latch)
int clockPin = 12; //Pin connected to Pin 11 of 74HC595 (Clock)
int dataPin = 11; //Pin connected to Pin 14 of 74HC595 (Data)

void setup() { //set pins to output
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  for (int i = 0; i < 256; i++) { //count from 0 to 255

    digitalWrite(latchPin, LOW); //set latchPin low to allow data flow
    shiftOut(i);
    digitalWrite(latchPin, HIGH); //set latchPin to high to lock and send data
    delay(500);

    Serial.println("for 1" + i);

  } //EndFor

}//End loop

void shiftOut(byte dataOut) {

  boolean pinState; // Shift out 8 bits LSB first, on rising edge of clock
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);

  for (int i = 0; i <= 7; i++) { // for each bit in dataOut send out a bit
    digitalWrite(clockPin, LOW); //set clockPin to LOW prior to sending bit

    if ( dataOut & (1 << i) ) { // if the value of DataOut and (logical AND) a bitmask are true, set pinState to 1 (HIGH)
      pinState = HIGH;
    } else {
      pinState = LOW;
    }

    digitalWrite(dataPin, pinState); //sets dataPin to HIGH or LOW depending on pinState

    digitalWrite(clockPin, HIGH); //send bit out on rising edge of clock

    Serial.println("for 2" + i);
  }

  digitalWrite(clockPin, LOW); //stop shifting out data

}
