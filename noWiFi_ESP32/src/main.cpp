# include <Arduino.h>
# include <appliance.h>
# include <led.h>


// Variables
Led led1(22);

Appliance washer;

void setup() {
  Serial.begin(115200);
  washer.intGreenSensor(13);
}

void loop() {
  
  Serial.println(washer.greenLed.read());
  delay(200);

  
  if (washer.greenLed.ledIsOn()) {
    led1.on();
  } else{
    led1.off();
  }
  
}