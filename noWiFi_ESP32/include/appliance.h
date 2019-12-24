# include <Arduino.h>
# include <ldr.h>

class Appliance{
    private:
        
    public:

        int off;
        int running;
        int finished;

        Ldr greenLed;
        Ldr orangeLed;

        Appliance(){
        };

    void intGreenLedSensor(int pin){
        greenLed = Ldr(pin);
    }
    
    void intOrangeLedSensor(int pin){
        orangeLed = Ldr(pin);
    }

};