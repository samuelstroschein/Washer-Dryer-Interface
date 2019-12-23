# include <Arduino.h>
# include <ldr.h>
# include <led.h>


// Variables
LED led1(22);
int ldrPin = 13;

void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);
}

void loop() {
  
  int ldrStatus = analogRead(ldrPin);
  Serial.println(ldrStatus);
  delay(200);

  if (ldrStatus >= 100) {
    led1.on();
  } else{
    led1.off();
  }
}