# include <Arduino.h>
# include <led.h>
# include <neotimer.h>


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
        Neotimer blinkingInterval = Neotimer(750);
        
    public:

        int running = 0;
        int finished = 0;

        Led workingLed;
        Led finishedLed;

        // initalization
        Appliance(int working, int finished){
            workingLed = Led(working);
            finishedLed = Led(finished);
            blinkingInterval.start();
        };


        // Methods 
        void clientInput(int inputRunning, int inputFinished){
            this->running = convertCharToInt(inputRunning);
            this->finished = convertCharToInt(inputFinished);
        }

        void finishedLedBlinking(){
            int blink = false;
            if (blinkingInterval.repeat()){
                blink = !blink;
            }
            if(blink){
                finishedLed.on();
            }
        }

        void processLights(){
            if (running == 1){
                workingLed.on();
                finishedLed.off();
            }
            else if (finished == 1){
                workingLed.off();
                finishedLedBlinking();
            }
            else {
                workingLed.off();
                finishedLed.off();
            }
        }

};