# include <Arduino.h>
# include <appliance.h>


// PINS
const int washerWorkingLedPin = 18;        //22
const int washerFinishedLedPin = 5;        //23
const int washerGreenLedSensorPin = 13;
const int washerOrangeLedSensorPin = 12;


/*
// LED STRIP PINS
const int greenPin1 = 18;
const int redPin1 = 5;

const int greenPin2 = 21;
const int redPin2 = 19;
*/


// Int with working led pin and finished led pin
Appliance washer(washerWorkingLedPin, washerFinishedLedPin);

void setup() {
  Serial.begin(115200); 
  washer.intGreenLedSensor(washerGreenLedSensorPin);
  washer.intOrangeLedSensor(washerOrangeLedSensorPin);

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

