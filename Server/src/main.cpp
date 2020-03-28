
# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <ESP8266WebServer.h>
# include <serverAppliance.h>


// Server
const char *ssid = "WDI_Server2";
const char *password = "macbook1";
ESP8266WebServer server(80);


// LED PINS

const int dryerFinishedLedPin = 16;
const int dryerRunningLedPin = 5;


const int washerFinishedLedPin = 12;
const int washerRunningLedPin = 15;   // led connected to GPIO2 (D4)


// Appliances
Appliance dryer(dryerRunningLedPin, dryerFinishedLedPin);
Appliance washer(washerRunningLedPin, washerFinishedLedPin);


void handleSentVar() {
  if (server.hasArg("sensor_reading")) { 
    // dataString = ["bool washerRunning, bool washerFinished, 
    //                bool dryerRunning, bool dryerFinished"]
    String dataString = server.arg("sensor_reading");

    washer.clientInput(dataString.charAt(0), dataString.charAt(1));
    dryer.clientInput(dataString.charAt(2), dataString.charAt(3));

    Serial.println(dataString.charAt(0));
    Serial.println(dataString);

    server.send(200, "text/html", "Data received");
  }
}

void setup() {

  Serial.begin(9600); //Default Baudrate

  delay(1000);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
}

void loop() {
  server.handleClient();
  washer.processLights();
  dryer.processLights();

}
