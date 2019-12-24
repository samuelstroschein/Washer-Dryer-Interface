# include <Arduino.h>
# include <ldr.h>

class Appliance{
    private:
        int off;
        int running;
        int finished;
        
    public:

        Ldr greenLed;
        Appliance(){
        };

    void intGreenSensor(int pin){
        greenLed = Ldr(pin);
    }
    
    void addOrangeSensor(int pin){
    }

};