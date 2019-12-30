# include <Arduino.h>
# include <neotimer.h>

class VibrationSensor {
    
    private:

        const int belowAverageReset = 10;
        const int aboveAverageRunning = 400;

        // Timer
        Neotimer falseAlarmTimer = Neotimer(10000);

        //Smoothing of the vibrationSensor data number of arrays multiplied with delay on line 38 = max duration of pause
        static const int numReadings = 10;
        float readings[numReadings];    // the readings from the analog input
        int readIndex = 0;              // the index of the current reading
        float total = 0;                // the running total
        float average = 0;              // the average

        // Pin
        int pin;

    public:

        // INIT
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
            readings[readIndex] = float(digitalRead(pin));
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
            this->average = float((total / numReadings));
        }
        
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



