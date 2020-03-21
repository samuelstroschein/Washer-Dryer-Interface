# include <Arduino.h>
# include <led.h>
# include <neotimer.h>


// Timer
Neotimer blinkingInterval = Neotimer(750);


// ? Still needed -> implemented in VibrationSensor class
// Neotimer minFalseAlarmTime = Neotimer(10000);


// Methods
int convertCharToInt(int charInput){
    if (charInput == 48){
        return 0;
    }
    else if (charInput == 49){
        return 1;
    }
}


class Appliance{
    private:
        
    public:

        int running = 0;
        int finished = 0;

        Led workingLed;
        Led finishedLed;

        Appliance(int working, int finished){
            workingLed = Led(working);
            finishedLed = Led(finished);
        };


        // Methods 
        void clientInput(int inputRunning, int inputFinished){
            this->running = convertCharToInt(inputRunning);
            this->finished = convertCharToInt(inputFinished);
        }

        void processLights(){
            if (running == 1){
                workingLed.on();
                finishedLed.off();
            }
            else if (finished == 1){
                workingLed.off();
                finishedLed.on();
            }
            else {
                workingLed.off();
                finishedLed.off();
            }
        }

};