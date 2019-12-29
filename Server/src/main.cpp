
# include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char *ssid = "WDI_Server2";
const char *password = "macbook1";

ESP8266WebServer server(80);

int washerRunningLed = 14;   // led connected to GPIO2 (D4)
int washerFinishedLed = 0;


void handleSentVar() {
  if (server.hasArg("sensor_reading")) { // this is the variable sent from the client
    int readingInt = server.arg("sensor_reading").toInt();

    if (readingInt == 10){
      digitalWrite(washerRunningLed, HIGH);
      digitalWrite(washerFinishedLed, LOW);
    }
    else if (readingInt == 11){
      digitalWrite(washerRunningLed, HIGH);
      digitalWrite(washerFinishedLed, HIGH);
    }
    else if (readingInt == 01){
      digitalWrite(washerRunningLed, LOW);
      digitalWrite(washerFinishedLed, HIGH);
    }
    else if (readingInt == 00){
      digitalWrite(washerRunningLed, LOW);
      digitalWrite(washerFinishedLed, LOW);
    }

    server.send(200, "text/html", "Data received");
  }
}

void setup() {

  Serial.begin(115200); //Default Baudrate
  pinMode(washerRunningLed, OUTPUT);
  pinMode(washerFinishedLed, OUTPUT);
  digitalWrite(washerRunningLed, LOW);
  digitalWrite(washerFinishedLed, LOW);

  delay(1000);


  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
}

void loop() {
  server.handleClient();
}
