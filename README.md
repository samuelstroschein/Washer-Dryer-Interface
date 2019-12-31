# Washer-Dryer-Interface
 
#### How it (currently) is supposed to work:
Vibration sensors at washer and dryer are measured over a time frame (currently 60 seconds). If a certain threshold is reached (20 vibrations measured in 60 secodns) then the appliance is considered running. If the vibrations measured fall below the threshold over the time period (probably extend the second time period, because washer emits less vibrations at the end) then the appliance is considered to be finished. A PIR sensor is placed above the dryer and washer. If appliance X is finished and the PIR sensor measures movement in front of the appliance it is assumed that a human being took care of the laundry and the finished LED turns off.

### TODO:
  * Fix Server CLient communication
    Continous WiFi connection drops.
  * Verify measurements of vibrations
  * Finish case for esp8266 in Fusion360
  * finish electronic circuit (parts are all available including 12V to 5V)
  
