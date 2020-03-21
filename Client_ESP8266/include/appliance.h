# include <Arduino.h>
# include <vibrationSensor.h>

class Appliance{
    private:
        VibrationSensor sensor;

        
    public:

        //? needed
        // int running;
        // int finished;

        Appliance(int vibrationSensorPin){
            VibrationSensor sensor(vibrationSensorPin);
        };

    int isRunning(){
        if (sensor.returnsIsRunning()){
            return true;
        }
    }

    int isFinished(){

    }

};
