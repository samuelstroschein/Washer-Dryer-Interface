# include <Arduino.h>

class LED {
    private:
        int pin;
    
    public:
        LED(int pin){
            this->pin = pin;
            init();
        }
    
    void init(){
        pinMode(pin, OUTPUT);
        off();
    }

    void on(){
        digitalWrite(pin, HIGH);
    }

    void off(){
        digitalWrite(pin, LOW);
    }
};