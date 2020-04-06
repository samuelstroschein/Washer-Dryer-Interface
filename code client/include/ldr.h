# include <Arduino.h>
# include <neotimer.h>

// 10k ohm resistor used

class Ldr {
    private:

        // threshold how many times the led was on in count() function
        static const int THRESHOLD_LED_ON = 27;
        static const int THRESHOLD_LED_BLINKING = 10;

        // numReadings * delayMeasure = total time measured. numReadings = 60 * delayMeasure = 1000 = 60 seconds
        static const int numReadings = 30;
        int readings[numReadings];      // the readings from the analog input
        int readIndex = 0;              // the index of the current reading
        int total = 0;                  // the running total

        Neotimer falseAlarmTimer = Neotimer(30000);

    public:
        // used to check initialization. if 0, then uninitalized
        int pin;

        Ldr(){
            this->pin = 0;
            init();
        }

        Ldr(int pin){
            this->pin = pin;
            init();
        }

        Ldr(int pin, int expectBlinking){
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

    int read(){
        int measure = analogRead(pin);
        if (measure >= 1){
            return 1;
        } else {
            return 0;
        }
    }

    void measure(){
            // subtract the last reading:
            total = total - readings[readIndex];
            // read from the sensor:
            readings[readIndex] = read();
            // add the reading to the total:
            total = total + readings[readIndex];
            // advance to the next position in the array:
            readIndex = readIndex + 1;
            // if we're at the end of the array...
            if (readIndex >= numReadings) {
                // ...wrap around to the beginning:
                readIndex = 0;
            }
            // called here because measure() is called in infinite loop
            falseAlarmTimerReset();
        }
    
    int count(){
        int result = 0;
        for (byte i = 0; i<numReadings; i++){
            if (readings[i] == 1){
                result += 1;
                }
            }
            return result;
    }

    int lightOn(){
        if (count() >= THRESHOLD_LED_ON){
            return true;
        }
        else{
            return false;
        }
    }

    int lightOff(){
        if (count() < THRESHOLD_LED_ON){
            return true;
        }
        else {
            return false;
        }
    }

    int lightBlinking(){
        if (THRESHOLD_LED_BLINKING < count() && count() < THRESHOLD_LED_ON && falseAlarmTimer.done()){
            return true;
        }
        else {
            return false;
        }
    }
    void falseAlarmTimerReset(){
            // reset timer
            if (count() <= 0){
                falseAlarmTimer.reset();
                falseAlarmTimer.start();
            }
        }
};




