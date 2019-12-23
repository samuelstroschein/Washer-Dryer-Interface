# include <Arduino.h>

// 220ohm resistor used

const int LED_ON_THRESHOLD = 100;

class Ldr {
    private:
        int pin;

    public:
        Ldr(int pin){
            this->pin = pin;
            init();
        }

    void init(){
        pinMode(pin, INPUT);
    }
    
    int read(){
        int result = analogRead(pin);
        return result;
    }

    int ledIsOn(){
        if (read() >= (LED_ON_THRESHOLD)){
            return true;
        } 
        else {
            return false;
        }

    }

};


