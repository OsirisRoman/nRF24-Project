#include "nRF24L01.h"
#include "RF24.h"
RF24 radio (7, 8);
#define BUTTON 2
#define LED 3
const byte addresses[][6] = {"00001",
"00002"};

boolean buttonState = 0;
boolean ledState = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  radio.begin();
  radio.setChannel(121);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
}

void loop(){


  delay(5);
  radio.startListening();
  while (!radio.available());
  radio.read(&ledState, sizeof(ledState));
  if(ledState == HIGH) {
      digitalWrite(LED, HIGH);
    }else {
      digitalWrite(LED, LOW);
    }

  delay(5);
  radio.stopListening();
  radio.write(&buttonState, sizeof(buttonState));
    // This is for getting the button input state.
   if(digitalRead(BUTTON) == HIGH && !buttonState) {
      buttonState = 1;
   }else if(digitalRead(BUTTON) == LOW && buttonState) {
        buttonState = 0;
   }
}
