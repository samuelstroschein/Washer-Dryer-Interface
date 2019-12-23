# include <Arduino.h>
# include <ldr.h>
# include <led.h>


// Variables
Led led1(22);
Ldr ldr1(13);

void setup() {
  Serial.begin(115200);
}

void loop() {
  
  Serial.println(ldr1.read());
  delay(200);

  if (ldr1.ledIsOn()) {
    led1.on();
  } else{
    led1.off();
  }
}