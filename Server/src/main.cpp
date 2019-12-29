
# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <ESP8266WebServer.h>
# include <appliance.h>


// Server
const char *ssid = "WDI_Server2";
const char *password = "macbook1";
ESP8266WebServer server(80);


// LED PINS
const int washerRunningLedPin = 14;   // led connected to GPIO2 (D4)
const int washerFinishedLedPin = 0;


// Appliances
Appliance washer(washerRunningLedPin, washerFinishedLedPin);


void handleSentVar() {
  if (server.hasArg("sensor_reading")) { // this is the variable sent from the client

    // dataString = ["bool washerRunning, bool washerFinished, 
    //                bool dryerRunning, bool dryerFinished"]
    String dataString = server.arg("sensor_reading");
    int dryerRunning = dataString.charAt(2);
    int dryerFinished = dataString.charAt(3);

    int testValue = dataString.substring(0,0).toInt();

    washer.clientInput(dataString.charAt(0), dataString.charAt(1));

    Serial.println(dataString.charAt(0));
    Serial.println(washer.running);

    server.send(200, "text/html", "Data received");
  }
}

void setup() {

  Serial.begin(115200); //Default Baudrate
  /*
  pinMode(washerRunningLedPin, OUTPUT);
  pinMode(washerFinishedLedPin, OUTPUT);
  digitalWrite(washerRunningLedPin, LOW);
  digitalWrite(washerFinishedLedPin, LOW);
  */

  delay(1000);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
}

void loop() {
  server.handleClient();
  washer.processAppliance();
}
