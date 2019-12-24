# include <Arduino.h>
# include <appliance.h>
# include <led.h>


// Variables
Led led1(22);
Led led2(23);

Appliance washer;

void setup() {
  Serial.begin(115200);
  washer.intGreenLedSensor(13);
  washer.intOrangeLedSensor(12);
}

void loop() {
  
  Serial.println(washer.greenLed.read());
  Serial.println(washer.orangeLed.read());
  Serial.println("\n");
  delay(200);


  
  if (washer.greenLed.ledIsOn()) {
    led1.on();
  } else{
    led1.off();
  }

  if (washer.orangeLed.ledIsOn()) {
    led2.on();
  } else{
    led2.off();
  }
}