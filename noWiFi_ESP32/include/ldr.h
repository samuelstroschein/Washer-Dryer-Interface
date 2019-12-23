# include <Arduino.h>

class LDR {
    private:
        int pin;

    public:
        LDR(int pin){
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
};


