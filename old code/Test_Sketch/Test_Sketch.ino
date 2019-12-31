

// these constants won't change:
const int ledPin = 13;      // LED connected to digital pin 13
const int sensor = 32; // the piezo is connected to analog pin 0
const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light


        // numReadings * delayMeasure = total time measured. numReadings = 60 * delayMeasure = 1000 = 60 seconds
        static const int numReadings = 10;
        int readings[numReadings]={0,0,0,0,0,0,0,0,0,0};      // the readings from the analog input
        int readIndex = 0;              // the index of the current reading
        int total = 0;                  // the running total
        // ? not needed anymore? (average)
        int average = 0;              // the average

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  pinMode(sensor, INPUT);
  Serial.begin(9600);       // use the serial port
}


void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = digitalRead(sensor);  
  //Serial.println(sensorReading);
  delay(2000);  // delay to avoid overloading the serial port buffer

  // subtract the last reading:
  // total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = sensorReading;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
     // ...wrap around to the beginning:
     readIndex = 0;
  }
  Serial.println(sensorReading);
  // Serial.println(digitalRead(sensorReading));
  /*
  Serial.println(readings[2]);
  Serial.println(countHighs());
  Serial.println("");
  */
  

}



int countHighs(){
            int result = 0;
            for (byte i = 0; i<numReadings; i++){
                if (readings[i] == 1){
                    result += 1;
                }
            }
            return result;
        }
        
  
