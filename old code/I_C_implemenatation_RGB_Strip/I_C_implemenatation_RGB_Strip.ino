/*I_C implementation of RGB LED strip
 */

#include <neotimer.h> //Uses millis from hardware to create a Timer.


//Smoothing of the vibrationSensor data number of arrays multiplied with delay on line 38 = max duration of pause
const int numReadings = 30;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


//pirSensor
int pirSensor = 16;
int motionCounter;                      //how many motions were detected? 2= went into the room and out = cleared dryer/washing mashine

// d= dryer
int dWorkingLed = 12;           //RED LED
int dFinishedLed = 14;          //GREEN LED
int dVibrationSensor = 9;
int dryerRunning;
int dryerFinished;
bool dLedBlink;

// w=washing machine
int wWorkingLed ;           //RED LED
int wFinishedLed ;          //GREEN LED
int wVibrationSensor ;
int washerRunning;
int washerFinished;
bool wLedBlink;

//Timer
Neotimer blinkingInterval = Neotimer(750);         //Intervall in welchem die LED blinken soll
Neotimer motionTimer = Neotimer(15000);              //how much time between detected motions in order to reset motionCounter
Neotimer dFalseAlarmTimeCheck = Neotimer(10000);     //Zeitraum in der sich die mindestens Geräte bewegen

void setup(){
  pinMode(dFinishedLed, OUTPUT);
  pinMode(dWorkingLed, OUTPUT);
  analogWrite(dFinishedLed, 0);
  analogWrite(dWorkingLed, 0);
 
  pinMode(dVibrationSensor, INPUT);
  pinMode(pirSensor, INPUT);  
  Serial.begin(9600); 
  digitalWrite(pirSensor, LOW);
  blinkingInterval.start();
  dFalseAlarmTimeCheck.start();

  
  //loop thisReadings from 0 till 9 (numReadings=10). Everytime add 1 (thisReading++)
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
  readings[thisReading] = 0;
  }
  
}

void loop(){
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(dVibrationSensor);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  delay(100); //for serial monitor


  //Wenn Vibration unter 1 fällt, wird die Variable zurückgesetzt.
  if (average <10){
    dFalseAlarmTimeCheck.reset();
    dFalseAlarmTimeCheck.start();
  }
  
  //if dFalseAlarmTimeCheck is above t (not restarted) then turn on working led
  if ((average > 400) && (dFalseAlarmTimeCheck.done())){
    dryerRunning = true;
    }
    
  if (dryerRunning == true){
    analogWrite(dWorkingLed,1000);
    analogWrite(dFinishedLed,0);
  }
  else {
    analogWrite(dWorkingLed, 0);
    analogWrite(dFinishedLed, 0);
  }

  if ((dryerRunning == true) && (average < 10)){
    dryerRunning = false;
    dryerFinished = true;
  }

  if (dryerFinished == true){
    analogWrite(dWorkingLed, 0);
    if (blinkingInterval.repeat()){
      dLedBlink = !dLedBlink;
    }
    if (dLedBlink){
      analogWrite(dFinishedLed, 1000);
    } else {
      analogWrite(dFinishedLed,0);
    }
  }
  
  if (digitalRead(pirSensor) == HIGH){
    motionCounter = motionCounter + 1;
    motionTimer.start();                                            //resume because function would restart timer every time otherwise
    //Serial.print("Motion Counter ");
    //Serial.print(motionCounter);
  }
  if (motionTimer.done()){
    motionCounter = 0;
    motionTimer.reset();
//    motionTimer.start();
    Serial.print(motionCounter);
  } 

  if (motionCounter >= 50){
    analogWrite(dFinishedLed, 0);
    dryerFinished = false;
//    Serial.print(" Dryer is finished");
   }
} 
