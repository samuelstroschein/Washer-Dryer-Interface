# include <Arduino.h>
# include <neotimer.h>

// outside of class because boolean values cant be in class in C++.... wow


class Led {
    private:
        int pin;
        Neotimer blinkingInterval = Neotimer(750); 
        bool blinkSwitch = false;
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
        blinkingInterval.start();
        off();
    }

    void on(){
        digitalWrite(pin, HIGH);
    }

    void off(){
        digitalWrite(pin, LOW);
    }

    void blink(){
        // every 750ms change BOOL value of blink
        if (blinkingInterval.repeat()){
            this->blinkSwitch = !blinkSwitch;
        }
        if(blinkSwitch){
            on();
        }
        else{
            off();
        }
    }
};