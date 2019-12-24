# include <Arduino.h>
# include <appliance.h>


// Variables

// Int with working led pin and finished led pin
Appliance washer(22, 23);

void setup() {
  Serial.begin(115200);
  washer.intGreenLedSensor(13);
  washer.intOrangeLedSensor(12);
}

void loop() {
  
  Serial.println(washer.greenLedSensor.read());
  Serial.println(washer.orangeLedSensor.read());
  Serial.println("\n");
  delay(200);


  
  if (washer.greenLedSensor.ledIsOn()) {
    washer.finishedLed.on();
  } else{
    washer.finishedLed.off();
  }

  if (washer.orangeLedSensor.ledIsOn()) {
    washer.workingLed.on();
  } else{
    washer.workingLed.off();
  }
}