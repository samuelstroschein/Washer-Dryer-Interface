# include <Arduino.h>

class LDR {
    private:
        int pin;

    public:
        int Ldr(int pin){
            init();
        }

    void init(){
        pinMode(pin, INPUT);
    }
    
    void read(){
        analogRead(pin);
    }
};


