# include <Arduino.h>
# include <ldr.h>

class Appliance{
    private:

    
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
        if (combinedSensor.pin != 0){
            if (combinedSensor.lightOn()){
                return true;
            } 
            else{
                return false;
            }
        }
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
        if (combinedSensor.pin != 0){
            if (combinedSensor.lightBlinking()){
                return true;
            } 
            else{
                return false;
            }
        }
        else {
            if (finishedSensor.lightOn()){
                return true;
            }
            else{
                return false;
            }
        }
    }
};
