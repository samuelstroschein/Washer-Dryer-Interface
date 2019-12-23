# include <Arduino.h>
# include <ldr.h>

// Variables
const int ledPin = 22;
const int ldrPin = 13;


void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  
  int ldrStatus = analogRead(ldrPin);
  Serial.println(ldrStatus);
  delay(200);

  if (ldrStatus >= 100) {
    digitalWrite(ledPin, HIGH);
  } else{
    digitalWrite(ledPin, LOW);
  }
}