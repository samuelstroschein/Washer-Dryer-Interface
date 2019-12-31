# include <Arduino.h>
# include <neotimer.h>

class VibrationSensor {
    
    private:

        //? still needed?
        const int belowAverageReset = 10;
        const int aboveAverageRunning = 400;

        // num of HIGH values in readinmmgs array
        const int runningAbove = 20;

        // Timer
        Neotimer falseAlarmTimer = Neotimer(10000);
        Neotimer delayMeasure = Neotimer(1000);


        // numReadings * delayMeasure = total time measured. numReadings = 60 * delayMeasure = 1000 = 60 seconds
        static const int numReadings = 60;
        int readings[numReadings];      // the readings from the analog input
        int readIndex = 0;              // the index of the current reading
        int total = 0;                  // the running total
        // ? not needed anymore? (average)
        int average = 0;                // the average

        // Pin
        int pin;

    public:

        // Initalization
        VibrationSensor(){
            this->pin = 0;
            init();
        }

        VibrationSensor(int pin){
            this->pin = pin;
            init();
        }

        void init(){
            pinMode(pin, INPUT);
            //loop thisReadings from 0 till 9 (numReadings=10). Everytime add 1 (thisReading++)
            for (int thisReading = 0; thisReading < numReadings; thisReading++) {
            readings[thisReading] = 0;
            }
        }
        
        // Debugging Methods
        int read(){
            int result = digitalRead(pin);
            return result;
        }

        int returnAverage(){
            return this->average;
        }

        // Methods
        void measure(){
            // subtract the last reading:
            total = total - readings[readIndex];
            // read from the sensor:
            readings[readIndex] = digitalRead(pin);
            // add the reading to the total:
            total = total + readings[readIndex];
            // advance to the next position in the array:
            readIndex = readIndex + 1;
            // if we're at the end of the array...
            if (readIndex >= numReadings) {
                // ...wrap around to the beginning:
                readIndex = 0;
            }
            /*
            // calculate the average:
            this->average = float((total / numReadings));
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


        //? needed anylonger?
        void falseAlarmCheck(){
            // reset timer
            if (this->average < belowAverageReset){
                falseAlarmTimer.reset();
                falseAlarmTimer.start();
            }
        }

        int applianceIsRunning(){
            if ((this->average >= aboveAverageRunning) && falseAlarmTimer.done()){
                return true;
            }
            else{
                return false;
            }
        }
};



