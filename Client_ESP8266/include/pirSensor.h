# include <Arduino.h>
# include <Neotimer.h>


class PirSensor{

    private:
        int pin;
        // how many movements must be detected (to prevent false alarm)
        int THRESHOLD = 3;
        //how much time between detected motions in order to reset motionCounter
        Neotimer motionTimer = Neotimer(15000);

    public:

        int motionCounter = 0;

        PirSensor(int inputPin){
            this->pin = inputPin;
            pinMode(this->pin, INPUT);  
        }

        void measure(){
            if (digitalRead(pin) == HIGH){
                this->motionCounter = this->motionCounter + 1;
                //resume because function would restart timer every time otherwise
                motionTimer.start();
            }
            if (motionTimer.done()){
                this->motionCounter = 0;
                motionTimer.reset();
            } 
        }
        
        int detectsPerson(){
            if (motionCounter >= THRESHOLD){
                return true;
            }
            else{
                return false;
            }
        }
};