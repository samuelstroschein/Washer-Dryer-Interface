# include <Arduino.h>
# include <vibrationSensor.h>

class Appliance{
    private:
        
    public:

        // int off;
        int running;
        int finished;

        Appliance(int vibrationSensorPin){
            VibrationSensor sensor(vibrationSensorPin);
        };

    bool isRunning(){
        
    }

};
