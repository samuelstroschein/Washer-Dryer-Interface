# include <Arduino.h>
# include <led.h>
# include <ldr.h>

class Appliance{
    private:
        
    public:

        int off;
        int running;
        int finished;

        Ldr greenLedSensor;
        Ldr orangeLedSensor;

        Led workingLed;
        Led finishedLed;

        Appliance(int working, int finished){
            workingLed = Led(working);
            finishedLed = Led(finished);
        };

    void intGreenLedSensor(int pin){
        greenLedSensor = Ldr(pin);
    }
    
    void intOrangeLedSensor(int pin){
        orangeLedSensor = Ldr(pin);
    }

};