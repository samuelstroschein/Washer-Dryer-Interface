# include <Arduino.h>
# include <ldr.h>
# include <neotimer.h>

class Appliance{
    private:
    // 7.2e6 = 2 hours 
    Neotimer finishedHeuristic = Neotimer(7.2e6);
    bool wasRunning = false;

    
    public:
        Ldr combinedSensor; // is On when appliance is runnning, Blinks when appliance is finished
        Ldr turnedOnSensor;
        Ldr finishedSensor;


        Appliance(int combinedSensorPin){
            combinedSensor = Ldr(combinedSensorPin);
        }
        Appliance(int turnedOnSensorPin, int finishedSensorPin){
            turnedOnSensor = Ldr(turnedOnSensorPin);
            finishedSensor = Ldr(finishedSensorPin);
        }

    int isRunning(){
        // checks if combinedSensor is initialised
        if (combinedSensor.pin != 0){
            if (combinedSensor.lightOn()){
                this->wasRunning = true;
                return true;
            } 
            else{
                return false;
            }
        }
        // if not use turnedOn and finished sensors
        else {
            if (turnedOnSensor.lightOn() && finishedSensor.lightOff()){
                return true;
            }
            else{
                return false;
            }
        }
    }

    int isFinished(){
        // checks if combinedSensor is initialised
        if (combinedSensor.pin != 0){
            if (combinedSensor.lightBlinking()){
                return true;
            }
            else if (combinedSensor.lightOff() && this->wasRunning == true){
                return true;
            }
            else{
                return false;
            }
        }
        // if not use turnedOn and finished sensors
        else {
            if (finishedSensor.lightOn()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    int wasEmptied(){
        this->wasRunning = false;
    }
};
