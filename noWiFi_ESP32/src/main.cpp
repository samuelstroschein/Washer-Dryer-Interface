# include <Arduino.h>
# include <ldr.h>
# include <led.h>


// Variables
LED led1(22);
LDR ldr1(13);

void setup() {
  Serial.begin(115200);
}

void loop() {
  
  Serial.println(ldr1.read());
  delay(200);

  if (ldr1.read() >= 100) {
    led1.on();
  } else{
    led1.off();
  }
}