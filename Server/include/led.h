# include <Arduino.h>

class Led {
    private:
        int pin;
    
    public:
    
        Led(){
            this->pin = 0;
            init();
        }


        Led(int pin){
            this->pin = pin;
            init();
        }
    
    void init(){
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        off();
    }

    void on(){
        digitalWrite(pin, HIGH);
    }

    void off(){
        digitalWrite(pin, LOW);
    }
};