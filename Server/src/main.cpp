
# include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char *ssid = "WDI_Server2";
const char *password = "macbook1";

ESP8266WebServer server(80);

int LED = 14;   // led connected to GPIO2 (D4)
int greenLed = 0;


void handleSentVar() {
  if (server.hasArg("sensor_reading")) { // this is the variable sent from the client
    int readingInt = server.arg("sensor_reading").toInt();

    if (readingInt >= 1){
      digitalWrite(LED, HIGH);
    }
    else{
      digitalWrite(LED, LOW);
    }

    server.send(200, "text/html", "Data received");
  }
}

void setup() {

  Serial.begin(115200); //Default Baudrate
  pinMode(LED, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(greenLed, LOW);

  delay(1000);


  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
}

void loop() {
  server.handleClient();
}
