#include <Arduino.h>

// pins
const int led = 15;
const int ldr = 12;



void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(ldr, INPUT);
}

void loop() {
  int ldrStatus = analogRead(ldr);

  Serial.println(ldrStatus);

  delay(100);


  
  if (ldrStatus <= 40){
    digitalWrite(led, HIGH);
    Serial.println("LDR IS DARK, LED IS ON");
  } else {
    digitalWrite(led, LOW);
    Serial.println("----");
  }
   
}