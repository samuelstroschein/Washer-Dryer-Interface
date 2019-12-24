# include <Arduino.h>
# include <ldr.h>

class Appliance{
    private:
        
    public:

        int off;
        int running;
        int finished;

        Ldr greenLedSensor;
        Ldr orangeLedSensor;

        Appliance(){
        };

    void intGreenLedSensor(int pin){
        greenLedSensor = Ldr(pin);
    }
    
    void intOrangeLedSensor(int pin){
        orangeLedSensor = Ldr(pin);
    }

};