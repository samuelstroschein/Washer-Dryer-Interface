# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <appliance.h>
# include <pirSensor.h>
# include <neotimer.h>

// Wifi server credentials
const char *ssid = "WDI_Server2";
const char *password = "macbook1";

// Pins of vibration sensor of appliances
const int washerSensorPin = 5;
//TODO assign value to dryer pin
const int dryerSensorPin;
const int pirPin = 0;

// Appliances
Appliance washer(washerSensorPin);
Appliance dryer(dryerSensorPin);


// PIR Sensor to detect emptying of appliances
PirSensor pirSensor(pirPin);

// query which contains the BOOLEAN values which light should be on
String dataString = "";



// --------------- definition of methods(functions) ------------------------


void appendDataString(Appliance appliance){
  if (appliance.isRunning()){
    dataString += "1";  // appliance running
    dataString += "0";  // appliance not finished
  }
  if (appliance.isFinished()){
    dataString += "0";  // appliance not running
    dataString += "1";  // appliance finished
  }
}



// ---------------------- START OF PROGRAM -----------------------

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
}


void loop() {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  // This is the order in which LED instructions are send. 
  // [WasherIsRunning, WasherIsFinished, DryerIsRunning, DryerIsFinished]
  dataString = "";

  washer.sensor.measure();
  dryer.sensor.measure();
  pirSensor.measure();

  // appends information about washer first e.g "01" (washer not running, washer finished)
  // then information about dryer e.g. "00" (dryer not running, dryer not finsihed)
  appendDataString(washer);
  appendDataString(dryer);

  

  // create a URI for the request. Something like /data/?sensor_reading=
  //                               [WasherIsRunning, WasherIsFinished, DryerIsRunning, DryerIsFinished]
  String url = "/data/";
  url += "?sensor_reading=";
  url += dataString;

  // send data string to server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 3000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // To turn off the finished status
  // double if statement because both can be finished at the same time
  if (pirSensor.detectsPerson()){
    if (washer.isFinished()){
      washer.wasEmptied();
    }
    if (dryer.isFinished()){
      dryer.wasEmptied();
    }
  }

  // Debug print statements  
    Serial.println(washer.sensor.read());
    Serial.println(washer.sensor.countHighs());
    Serial.println(washer.isRunning());
    Serial.println(washer.isFinished());
    Serial.println(url);
    Serial.println("");
    Serial.println(pirSensor.motionCounter);
    Serial.println(pirSensor.detectsPerson());
    Serial.println("");
  
  delay(1000);
}