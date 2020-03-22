# include <Arduino.h>
# include <vibrationSensor.h>

class Appliance{
    private:
        int running;    // logic programmed in VibrationSensor class

        
    public:
        // int wasRunning; // logic programmed in main, therefore public
        // int finished;   // logic programmed in main, therefore public

        VibrationSensor sensor;

        Appliance(int vibrationSensorPin){
            sensor = VibrationSensor(vibrationSensorPin);
        };

    // threshold for isRunning programmed in VibrationSensor class
    int isRunning(){
        if (sensor.returnsIsRunning()){
            return true;
        } else{
            return false;
        }
    }

    int isFinished(){
        if (sensor.returnsIsFinished()){
            return true;
        } else {
            return false;
        }
    }

};
